#pragma once
#include "Saturn/Renderer/Shader.h"

typedef unsigned int GLenum;

namespace Saturn
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		OpenGLShader(const std::string& filepath);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetVec2f(const std::string& name, const glm::vec2& value) override;
		virtual void SetVec3f(const std::string& name, const glm::vec3& value) override;
		virtual void SetVec4f(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat3f(const std::string& name, const glm::mat3& value) override;
		virtual void SetMat4f(const std::string& name, const glm::mat4& value) override;

		virtual const std::string& GetName() const override { return m_Name; }

		void UploadUniformInt(const std::string& name, int value);
		void UploadUniformIntArray(const std::string& name, int* values, uint32_t count);
		void UploadUniformFloat(const std::string& name, float value);
		void UploadUniformVec2f(const std::string& name, const glm::vec2& vector);
		void UploadUniformVec3f(const std::string& name, const glm::vec3& vector);
		void UploadUniformVec4f(const std::string& name, const glm::vec4& vector);

		void UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> Preprocess(const std::string& shaderSrc);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSrcs);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};
}
