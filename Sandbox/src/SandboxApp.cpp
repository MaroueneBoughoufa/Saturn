#include <Saturn.h>
#include <ImGui/imgui.h>

#include <Platform/OpenGL/OpenGLShader.h>
#include <glm/gtc/matrix_transform.hpp>

class GameLayer : public Saturn::Layer
{
public:
	GameLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_SquarePosition(0.0f)
	{
		m_SquareVA = Saturn::VertexArray::Create();
		
		float squareVertices[] = {
			// Position          // TexCoords
			0.5f,  0.5f,  0.0f,  1.0f, 1.0f,  // top right
			0.5f, -0.5f,  0.0f,  1.0f, 0.0f,  // bottom right
		   -0.5f, -0.5f,  0.0f,  0.0f, 0.0f,  // bottom left
		   -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  // top left
		};

		Saturn::Ref<Saturn::VertexBuffer> squareVB = Saturn::VertexBuffer::Create(squareVertices, sizeof(squareVertices));

		squareVB->SetLayout({
			{ Saturn::ShaderDataType::Vec3f, "a_Position" },
			{ Saturn::ShaderDataType::Vec2f, "a_TexCoord" }
		});
		
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[] = {
			0, 1, 3,
			1, 2, 3
		};

		Saturn::Ref<Saturn::IndexBuffer> squareIndexBuffer = Saturn::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVA->SetIndexBuffer(squareIndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TexCoord;

			void main()
			{
				v_TexCoord = a_TexCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec2 v_TexCoord;
			uniform sampler2D u_Texture;
			
			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		m_Shader = Saturn::Shader::Create(vertexSrc, fragmentSrc);

		m_Texture = Saturn::Texture2D::Create("assets/textures/alpha-test.png");

		std::dynamic_pointer_cast<Saturn::OpenGLShader>(m_Shader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Saturn::Timestep ts) override
	{
		if (Saturn::Input::IsKeyPressed(KEY_LEFT))
			m_CameraPosition.x -= m_CameraSpeed * ts;
		else if (Saturn::Input::IsKeyPressed(KEY_RIGHT))
			m_CameraPosition.x += m_CameraSpeed * ts;
		
		if (Saturn::Input::IsKeyPressed(KEY_UP))
			m_CameraPosition.y += m_CameraSpeed * ts;
		else if (Saturn::Input::IsKeyPressed(KEY_DOWN))
			m_CameraPosition.y -= m_CameraSpeed * ts;

		if (Saturn::Input::IsKeyPressed(KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Saturn::Input::IsKeyPressed(KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		if (Saturn::Input::IsKeyPressed(KEY_J))
			m_SquarePosition.x -= m_SquareSpeed * ts;
		else if (Saturn::Input::IsKeyPressed(KEY_L))
			m_SquarePosition.x += m_SquareSpeed * ts;

		if (Saturn::Input::IsKeyPressed(KEY_I))
			m_SquarePosition.y += m_SquareSpeed * ts;
		else if (Saturn::Input::IsKeyPressed(KEY_K))
			m_SquarePosition.y -= m_SquareSpeed * ts;

		m_Texture->Bind();

		Saturn::RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1));
		Saturn::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Saturn::Renderer::BeginScene(m_Camera);

		Saturn::RenderCommand::SetWireframeMode(false);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition);

		Saturn::Renderer::Submit(m_Shader, m_SquareVA, transform);

		Saturn::Renderer::EndScene();
	}

	void OnEvent(Saturn::Event& event) override
	{
	}

	void OnImGuiRender() override
	{
	}

private:
	Saturn::Ref<Saturn::VertexArray> m_SquareVA;
	Saturn::Ref<Saturn::Shader> m_Shader;
	Saturn::Ref<Saturn::Texture2D> m_Texture;

	Saturn::OrthoCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 3.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 60.0f;

	glm::vec3 m_SquarePosition;
	float m_SquareSpeed = 1.5f;
};

class Sandbox : public Saturn::Application
{
public:
	Sandbox()
	{
		PushLayer(new GameLayer());
	}

	~Sandbox()
	{

	}
};

Saturn::Application* Saturn::CreateApplication()
{
	return new Sandbox();
}
