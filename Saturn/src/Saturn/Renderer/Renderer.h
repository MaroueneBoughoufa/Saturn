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
		static void Init();
		static void ShutDown();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthoCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4 transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static Scope<SceneData> s_SceneData;
	};
}
