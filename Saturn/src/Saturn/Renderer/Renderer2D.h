#pragma once

#include "OrthoCamera.h"
#include "Texture.h"

namespace Saturn
{
	struct Quad
	{
		glm::vec2 position{ 0.0f, 0.0f };
		glm::vec2 size{ 1.0f, 1.0f };
		glm::vec4 color{ 1.0f };
	};

	class Renderer2D
	{
	public:
		static void Init();
		static void ShutDown();

		static void BeginScene(const OrthoCamera& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(Quad& quad);
		
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color = glm::vec4(1.0f));

		
		static void DrawQuad(Quad& quad, Ref<Texture> texture);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, const glm::vec4& tint = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, const glm::vec4& tint = glm::vec4(1.0f));

		// Rotated Quads
		static void DrawRotatedQuad(Quad& quad, float rotation = 0.0f);

		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation = 0.0f, const glm::vec4 & color = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation = 0.0f, const glm::vec4& color = glm::vec4(1.0f));

		static void DrawRotatedQuad(Quad& quad, Ref<Texture> texture, float rotation = 0.0f);

		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture>& texture, float rotation = 0.0f, const glm::vec4& tint = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture>& texture, float rotation = 0.0f, const glm::vec4& tint = glm::vec4(1.0f));
	};
}
