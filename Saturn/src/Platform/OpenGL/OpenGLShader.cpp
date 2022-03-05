#include "stpch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

namespace Saturn
{
	OpenGLShader::OpenGLShader(const std::string vertexSrc, const std::string fragmentSrc)
	{
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = (const GLchar*)vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLenght = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLenght);

			std::vector<GLchar> infoLog(maxLenght);
			glGetShaderInfoLog(vertexShader, maxLenght, &maxLenght, &infoLog[0]);

			glDeleteShader(vertexShader);

			ST_CORE_ERROR("{0}", infoLog.data());
			ST_CORE_ASSERT(false, "Vertex shader compilation failed!");
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = (const GLchar*)fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		glCompileShader(fragmentShader);

		isCompiled = 0;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLenght = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLenght);

			std::vector<GLchar> infoLog(maxLenght);
			glGetShaderInfoLog(fragmentShader, maxLenght, &maxLenght, &infoLog[0]);

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			ST_CORE_ERROR("{0}", infoLog.data());
			ST_CORE_ASSERT(false, "Fragment shader compilation failed!");

			return;
		}

		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

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

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			ST_CORE_ERROR("{0}", infoLog.data());
			ST_CORE_ASSERT(false, "Shader linking failed!");

			return;
		}

		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}
}