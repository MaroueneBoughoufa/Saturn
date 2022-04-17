#pragma once

#include "Saturn/Renderer/RendererAPI.h"

namespace Saturn
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t height, uint32_t width) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;

		virtual void SetWireframeMode(bool wireframe) override;
	};
}
