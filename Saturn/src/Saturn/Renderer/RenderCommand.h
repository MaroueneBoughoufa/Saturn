#pragma once

#include "RendererAPI.h"

namespace Saturn
{
	class RenderCommand
	{
	public:
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