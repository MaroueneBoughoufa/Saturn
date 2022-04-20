#pragma once

#include "Saturn/Renderer/OrthoCamera.h"

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
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color = { 0.0f, 0.0f, 0.0f, 1.0f });
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color = { 0.0f, 0.0f, 0.0f, 1.0f });
	};
}
