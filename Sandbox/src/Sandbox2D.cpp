#include "Sandbox2D.h"

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	m_Texture = Saturn::Texture2D::Create("assets/textures/alpha-test.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Saturn::Timestep ts)
{
	ST_PROFILE_FUNCTION();

	// Update
	{
		ST_PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Render
	{
		ST_PROFILE_SCOPE("Renderer Prep");
		Saturn::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Saturn::RenderCommand::Clear();
	}

	{
		ST_PROFILE_SCOPE("Renderer Draw");
		Saturn::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Saturn::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, m_SquareColor);
		Saturn::Renderer2D::DrawQuad({ 0.5f, -0.1f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Saturn::Renderer2D::DrawQuad({ 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f }, m_Texture, m_SquareColor);
		Saturn::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnEvent(Saturn::Event& e)
{
	m_CameraController.OnEvent(e);
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	//ImGui::DragFloat("Square Rotation", &m_SquareRotation);
	//ImGui::DragFloat2("Square Size", glm::value_ptr(m_SquareSize), 0.1f);
	ImGui::End();
}
