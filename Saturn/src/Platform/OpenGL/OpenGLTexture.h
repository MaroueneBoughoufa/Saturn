#pragma once

#include "Saturn/Renderer/Texture.h"

namespace Saturn
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& filepath);
		~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		std::string m_FilePath;
		uint32_t m_Width, m_Height;

		uint32_t m_RendererID;
	};
}
