#include <Saturn.h>
#include <ImGui/imgui.h>

class GameLayer : public Saturn::Layer
{
public:
	GameLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Saturn::VertexArray::Create());
		
		float vertices[] = {
			// Position           // Color
			0.5f,  0.5f,  0.0f,   0.8f, 0.2f, 0.8f, 1.0f,  // top right
			0.5f, -0.5f,  0.0f,   0.2f, 0.3f, 0.8f, 1.0f,  // bottom right
		   -0.5f, -0.5f,  0.0f,   0.8f, 0.8f, 0.2f, 1.0f,  // bottom left
		   -0.5f,  0.5f,  0.0f,   0.3f, 0.2f, 0.8f, 1.0f   // top left
		};

		m_VertexBuffer.reset(Saturn::VertexBuffer::Create(vertices, sizeof(vertices)));

		Saturn::BufferLayout layout = {
			{ Saturn::ShaderDataType::Vec3f, "a_Position" },
			{ Saturn::ShaderDataType::Vec4f, "a_Color" }
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[] = {
			0, 1, 3,
			1, 2, 3
		};

		m_IndexBuffer.reset(Saturn::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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
		ST_TRACE("Delta time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMiliseconds());

		if (Saturn::Input::IsKeyPressed(KEY_LEFT))
			m_CameraPosition.x -= m_CameraSpeed;
		else if (Saturn::Input::IsKeyPressed(KEY_RIGHT))
			m_CameraPosition.x += m_CameraSpeed;
		
		if (Saturn::Input::IsKeyPressed(KEY_UP))
			m_CameraPosition.y += m_CameraSpeed;
		else if (Saturn::Input::IsKeyPressed(KEY_DOWN))
			m_CameraPosition.y -= m_CameraSpeed;

		if (Saturn::Input::IsKeyPressed(KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed;
		else if (Saturn::Input::IsKeyPressed(KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed;

		Saturn::RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1));
		Saturn::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Saturn::Renderer::BeginScene(m_Camera);

		Saturn::RenderCommand::SetWireframeMode(false);

		Saturn::Renderer::Submit(m_Shader, m_VertexArray);

		Saturn::Renderer::EndScene();
	}

	void OnEvent(Saturn::Event& event) override
	{
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Some random text.");
		ImGui::End();
	}
private:
	std::shared_ptr<Saturn::VertexArray> m_VertexArray;
	std::shared_ptr<Saturn::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Saturn::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Saturn::Shader> m_Shader;

	Saturn::OrthoCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 0.1f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 2.0f;
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
