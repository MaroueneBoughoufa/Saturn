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

	//Temp
	//Saturn::ShaderLib m_ShaderLib;
	Saturn::Ref<Saturn::Shader> m_TextureShader;
	Saturn::Ref<Saturn::Shader> m_FlatColorShader;
	Saturn::Ref<Saturn::Texture2D> m_Texture;
	Saturn::Ref<Saturn::VertexArray> m_SquareVA, m_TexVA;
	
	glm::vec4 m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};
};
