#pragma once

#include "RenderCommand.h"
#include "OrthoCamera.h"
#include "Shader.h"

#include <glm/glm.hpp>

namespace Saturn
{
	class Renderer
	{
	public:
		static void BeginScene(OrthoCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4 tranform = glm::mat4(0.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};
}
