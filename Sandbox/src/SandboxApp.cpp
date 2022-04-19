#include <Saturn.h>
#include <Saturn/Core/EntryPoint.h>
#include <ImGui/imgui.h>

#include <Platform/OpenGL/OpenGLShader.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Sandbox2D.h"

class GameLayer : public Saturn::Layer
{
public:
	GameLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
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

		m_Shader = Saturn::Shader::Create("assets/shaders/Texture.glsl");

		m_Texture = Saturn::Texture2D::Create("assets/textures/alpha-test.png");

		std::dynamic_pointer_cast<Saturn::OpenGLShader>(m_Shader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Saturn::Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);

		m_Texture->Bind();

		Saturn::RenderCommand::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1));
		Saturn::RenderCommand::Clear();

		Saturn::Renderer::BeginScene(m_CameraController.GetCamera());

		Saturn::Renderer::Submit(m_Shader, m_SquareVA);

		Saturn::Renderer::EndScene();
	}

	void OnEvent(Saturn::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

	void OnImGuiRender() override
	{
	}

private:
	Saturn::Ref<Saturn::VertexArray> m_SquareVA;
	Saturn::Ref<Saturn::Shader> m_Shader;
	Saturn::Ref<Saturn::Texture2D> m_Texture;

	Saturn::OrthoCameraController m_CameraController;
};

class Sandbox : public Saturn::Application
{
public:
	Sandbox()
	{
		//PushLayer(new GameLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Saturn::Application* Saturn::CreateApplication()
{
	return new Sandbox();
}
