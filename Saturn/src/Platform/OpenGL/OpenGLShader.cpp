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

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string src = ReadFile(filepath);
		auto shaderSources = Preprocess(src);
		Compile(shaderSources);
	}

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}


	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSrcs)
	{
		GLuint program = glCreateProgram();
		std::vector<GLenum> glShaderIDs(shaderSrcs.size());
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
			glShaderIDs.push_back(shader);
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
			glDetachShader(program, id);
		
		m_RendererID = program;
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream in(filepath, std::ios::in, std::ios::binary);
		if (in)
		{
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
		}
		else
		{
			ST_CORE_ERROR("Could not open file '{0}'.", filepath);
		}

		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::Preprocess(const std::string& shaderSrc)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = shaderSrc.find(typeToken, 0);
		
		while (pos != std::string::npos)
		{
			size_t eol = shaderSrc.find_first_of("\r\n", pos);
			ST_CORE_ASSERT(eol != std::string::npos, "Syntax Error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = shaderSrc.substr(begin, eol - begin);
			ST_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specification!");

			size_t nextLinePos = shaderSrc.find_first_not_of("\r\n", eol);
			pos = shaderSrc.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = shaderSrc.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? shaderSrc.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
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
