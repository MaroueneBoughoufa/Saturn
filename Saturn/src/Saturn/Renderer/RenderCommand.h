#pragma once

#include "RendererAPI.h"

namespace Saturn
{
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t height, uint32_t width)
		{
			s_RendererAPI->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}

		inline static void SetWireframeMode(bool wireframe)
		{
			s_RendererAPI->SetWireframeMode(wireframe);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};
}
