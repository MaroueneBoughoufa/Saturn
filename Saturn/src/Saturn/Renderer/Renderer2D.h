#pragma once

#include "OrthoCamera.h"
#include "Texture.h"

namespace Saturn
{
	class Renderer2D
	{
	public:
		static void Init();
		static void ShutDown();

		static void BeginScene(const OrthoCamera& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color = glm::vec4(1.0f), float rotation = 0.0f);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color = glm::vec4(1.0f), float rotation = 0.0f);
		
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, float rotation = 0.0f, const glm::vec4& tint = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, float rotation = 0.0f, const glm::vec4& tint = glm::vec4(1.0f));
	};
}
