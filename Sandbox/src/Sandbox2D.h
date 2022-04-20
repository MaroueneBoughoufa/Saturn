#pragma once

#include <Saturn.h>

class Sandbox2D : public Saturn::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Saturn::Timestep ts) override;
	void OnEvent(Saturn::Event& e) override;
	void OnImGuiRender() override;
private:
	Saturn::OrthoCameraController m_CameraController;
	
	Saturn::Ref<Saturn::Texture2D> m_Texture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec2 m_SquareSize = { 1.0f, 1.0f };
	float m_SquareRotation = 0.0f;
};
