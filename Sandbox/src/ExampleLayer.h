#pragma once

#include <Saturn.h>

class ExampleLayer : public Saturn::Layer
{
public:
	ExampleLayer();

	void OnAttach() override;
	void OnDetach() override;

	void OnUpdate(Saturn::Timestep ts) override;
	void OnEvent(Saturn::Event& e) override;
private:
	Saturn::Ref<Saturn::VertexArray> m_SquareVA;
	Saturn::Ref<Saturn::Shader> m_Shader;
	Saturn::Ref<Saturn::Texture2D> m_Texture;

	Saturn::OrthoCameraController m_CameraController;
};
