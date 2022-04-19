#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_SquareVA = Saturn::VertexArray::Create();
	m_TexVA = Saturn::VertexArray::Create();
	
	{
		float squareVertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Saturn::Ref<Saturn::VertexBuffer> squareVB = Saturn::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ Saturn::ShaderDataType::Vec3f, "a_Position"}
		});
		m_SquareVA->AddVertexBuffer(squareVB);
	}

	{
		float texVertices[] = {
			// Position          // TexCoords
			0.5f,  0.5f,  0.0f,  1.0f, 1.0f,  // top right
			0.5f, -0.5f,  0.0f,  1.0f, 0.0f,  // bottom right
		   -0.5f, -0.5f,  0.0f,  0.0f, 0.0f,  // bottom left
		   -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  // top left
		};

		Saturn::Ref<Saturn::VertexBuffer> texVB = Saturn::VertexBuffer::Create(texVertices, sizeof(texVertices));
		texVB->SetLayout({
			{ Saturn::ShaderDataType::Vec3f, "a_Position" },
			{ Saturn::ShaderDataType::Vec2f, "a_TexCoord" }
		});
		m_TexVA->AddVertexBuffer(texVB);
	}

	uint32_t squareIndices[] = { 0, 1, 2, 2, 3, 0 };
	
	Saturn::Ref<Saturn::IndexBuffer> squareIB = Saturn::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_SquareVA->SetIndexBuffer(squareIB);

	Saturn::Ref<Saturn::IndexBuffer> texIB = Saturn::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
	m_TexVA->SetIndexBuffer(texIB);

	m_Texture = Saturn::Texture2D::Create("assets/textures/alpha-test.png");

	m_TextureShader = Saturn::Shader::Create("assets/shaders/Texture.glsl");

	m_TextureShader->Bind();
	m_TextureShader->SetInt("u_Texture", 0);

	m_FlatColorShader = Saturn::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Saturn::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Saturn::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	Saturn::RenderCommand::Clear();

	m_Texture->Bind();
	
	Saturn::Renderer::BeginScene(m_CameraController.GetCamera());

	m_FlatColorShader->Bind();
	m_FlatColorShader->SetVec4f("u_Color", m_SquareColor);

	
	Saturn::Renderer::Submit(m_FlatColorShader, m_SquareVA);
	
	Saturn::Renderer::Submit(m_TextureShader, m_TexVA);

	Saturn::Renderer::EndScene();
}

void Sandbox2D::OnEvent(Saturn::Event& e)
{
	m_CameraController.OnEvent(e);
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}
