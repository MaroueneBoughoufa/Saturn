#include <Saturn.h>
#include <ImGui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>

class GameLayer : public Saturn::Layer
{
public:
	GameLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_SquarePosition(0.0f)
	{
		Saturn::BufferLayout layout = {
			{ Saturn::ShaderDataType::Vec3f, "a_Position" },
			{ Saturn::ShaderDataType::Vec4f, "a_Color" }
		};

		m_SquareVA.reset(Saturn::VertexArray::Create());
		
		float squareVertices[] = {
			// Position           // Color
			0.5f,  0.5f,  0.0f,   0.8f, 0.2f, 0.8f, 1.0f,  // top right
			0.5f, -0.5f,  0.0f,   0.2f, 0.3f, 0.8f, 1.0f,  // bottom right
		   -0.5f, -0.5f,  0.0f,   0.8f, 0.8f, 0.2f, 1.0f,  // bottom left
		   -0.5f,  0.5f,  0.0f,   0.3f, 0.2f, 0.8f, 1.0f   // top left
		};

		std::shared_ptr<Saturn::VertexBuffer> squareVertexBuffer;
		squareVertexBuffer.reset(Saturn::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));


		squareVertexBuffer->SetLayout(layout);
		m_SquareVA->AddVertexBuffer(squareVertexBuffer);

		uint32_t squareIndices[] = {
			0, 1, 3,
			1, 2, 3
		};

		std::shared_ptr<Saturn::IndexBuffer> squareIndexBuffer;

		squareIndexBuffer.reset(Saturn::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIndexBuffer);

		m_VertexArray.reset(Saturn::VertexArray::Create());

		float vertices[] = {
			 0.0f,  0.5f,  0.0f,   1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f,  0.0f,   1.0f, 0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f,  0.0f,   1.0f, 0.0f, 0.0f, 1.0f
		};

		std::shared_ptr<Saturn::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Saturn::VertexBuffer::Create(vertices, sizeof(vertices)));

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[] = {
			1, 2, 3
		};

		std::shared_ptr<Saturn::IndexBuffer> indexBuffer;
		indexBuffer.reset(Saturn::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
			
			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader.reset(Saturn::Shader::Create(vertexSrc, fragmentSrc));
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

		Saturn::RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1));
		Saturn::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Saturn::Renderer::BeginScene(m_Camera);

		Saturn::RenderCommand::SetWireframeMode(false);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition);

		Saturn::Renderer::Submit(m_Shader, m_SquareVA, transform);
		Saturn::Renderer::Submit(m_Shader, m_VertexArray);

		Saturn::Renderer::EndScene();
	}

	void OnEvent(Saturn::Event& event) override
	{
	}

	void OnImGuiRender() override
	{
	}
private:
	std::shared_ptr<Saturn::VertexArray> m_VertexArray;
	std::shared_ptr<Saturn::VertexArray> m_SquareVA;
	std::shared_ptr<Saturn::Shader> m_Shader;

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
