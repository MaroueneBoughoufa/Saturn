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
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Saturn::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Saturn::RenderCommand::Clear();

	Saturn::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Saturn::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.0f }, m_SquareSize, m_SquareColor, m_SquareRotation);
	Saturn::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.0f }, m_SquareSize, m_Texture, m_SquareRotation);
	Saturn::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Saturn::Event& e)
{
	m_CameraController.OnEvent(e);
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::DragFloat("Square Rotation", &m_SquareRotation);
	ImGui::DragFloat2("Square Size", glm::value_ptr(m_SquareSize), 0.1f);
	ImGui::End();
}
