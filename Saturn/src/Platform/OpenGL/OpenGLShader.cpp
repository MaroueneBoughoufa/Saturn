#include "stpch.h"
#include "OpenGLShader.h"

#include <fstream>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Saturn
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex") return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;

		ST_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		ST_PROFILE_FUNCTION();

		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
	{
		ST_PROFILE_FUNCTION();

		UploadUniformIntArray(name, values, count);
	}

	void OpenGLShader::SetFloat(const std::string& name, float value)
	{
		ST_PROFILE_FUNCTION();

		UploadUniformFloat(name, value);
	}

	void OpenGLShader::SetVec2f(const std::string& name, const glm::vec2& value)
	{
		ST_PROFILE_FUNCTION();

		UploadUniformVec2f(name, value);
	}

	void OpenGLShader::SetVec3f(const std::string& name, const glm::vec3& value)
	{
		ST_PROFILE_FUNCTION();

		UploadUniformVec3f(name, value);
	}

	void OpenGLShader::SetVec4f(const std::string& name, const glm::vec4& value)
	{
		ST_PROFILE_FUNCTION();

		UploadUniformVec4f(name, value);
	}

	void OpenGLShader::SetMat4f(const std::string& name, const glm::mat4& value)
	{
		ST_PROFILE_FUNCTION();

		UploadUniformMat4(name, value);
	}

	void OpenGLShader::SetMat3f(const std::string& name, const glm::mat3& value)
	{
		ST_PROFILE_FUNCTION();

		UploadUniformMat3(name, value);
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		ST_PROFILE_FUNCTION();

		std::string src = ReadFile(filepath);
		auto shaderSources = Preprocess(src);
		Compile(shaderSources);

		// Extract name form file path
		auto lastSlash = filepath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.rfind(".");
		auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		: m_Name(name)
	{
		ST_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}


	OpenGLShader::~OpenGLShader()
	{
		ST_PROFILE_FUNCTION();

		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSrcs)
	{
		ST_PROFILE_FUNCTION();

		GLuint program = glCreateProgram();
		ST_CORE_ASSERT(shaderSrcs.size() <= 2, "Only 2 shaders can be supported for now.");
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;

		for (auto kv : shaderSrcs)
		{
			GLenum type = kv.first;
			const std::string& src = kv.second;

			GLuint shader = glCreateShader(type);

			const GLchar* source = (const GLchar*)src.c_str();
			glShaderSource(shader, 1, &source, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLenght = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLenght);

				std::vector<GLchar> infoLog(maxLenght);
				glGetShaderInfoLog(shader, maxLenght, &maxLenght, &infoLog[0]);

				glDeleteShader(shader);

				ST_CORE_ERROR("{0}", infoLog.data());
				ST_CORE_ASSERT(false, "Shader compilation failed!");
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLenght = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLenght);

			std::vector<GLchar> infoLog(maxLenght);
			glGetProgramInfoLog(program, maxLenght, &maxLenght, &infoLog[0]);

			glDeleteProgram(program);

			for (auto id : glShaderIDs)
				glDeleteShader(id);

			ST_CORE_ERROR("{0}", infoLog.data());
			ST_CORE_ASSERT(false, "Shader linking failed!");

			return;
		}

		for (auto id : glShaderIDs)
		{
			glDetachShader(program, id);
			glDeleteShader(id);
		}
		
		m_RendererID = program;
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		ST_PROFILE_FUNCTION();

		std::string result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			size_t size = in.tellg();
			if (size != -1)
			{
				result.resize(size);
				in.seekg(0, std::ios::beg);
				in.read(&result[0], size);
				in.close();
			}
			else
			{
				ST_CORE_ERROR("Could not read from file '{0}'", filepath);
			}
		}
		else
		{
			ST_CORE_ERROR("Could not open file '{0}'.", filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::Preprocess(const std::string& shaderSrc)
	{
		ST_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = shaderSrc.find(typeToken, 0); // Start of shader type declaration line
		
		while (pos != std::string::npos)
		{
			size_t eol = shaderSrc.find_first_of("\r\n", pos); // End of shader type declaration line
			ST_CORE_ASSERT(eol != std::string::npos, "Syntax Error");
			size_t begin = pos + typeTokenLength + 1; // Start of shader type name (after "#type " keyword)
			std::string type = shaderSrc.substr(begin, eol - begin);
			ST_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specification!");

			size_t nextLinePos = shaderSrc.find_first_not_of("\r\n", eol); // Start of shader code after shader type declaration line
			ST_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax Error.");

			pos = shaderSrc.find(typeToken, nextLinePos); // Start of next shader type declaration line
			shaderSources[ShaderTypeFromString(type)] = shaderSrc.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? shaderSrc.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Bind() const
	{
		ST_PROFILE_FUNCTION();

		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		ST_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, count, values);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformVec2f(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformVec3f(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformVec4f(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}
