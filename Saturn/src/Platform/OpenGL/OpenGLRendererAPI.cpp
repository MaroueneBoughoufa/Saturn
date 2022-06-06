#include "stpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Saturn
{
	void OpenGLMessageCallback (
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int lenght,
		const char* message,
		const void* userParam
	)
	{
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         ST_CORE_CRITICAL(message); return;
			case GL_DEBUG_SEVERITY_MEDIUM:       ST_CORE_ERROR(message); return;
			case GL_DEBUG_SEVERITY_LOW:          ST_CORE_WARN(message); return;
			case GL_DEBUG_SEVERITY_NOTIFICATION: ST_CORE_TRACE(message); return;
		}

		ST_CORE_ASSERT(false, "Unkown severity level!");
	}

	void OpenGLRendererAPI::Init()
	{
		ST_PROFILE_FUNCTION();

#ifdef ST_DEBUG
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t height, uint32_t width)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		uint32_t count = indexCount ? vertexArray->GetIndexBuffer()->GetCount() : indexCount;
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLRendererAPI::SetWireframeMode(bool wireframe)
	{
		if (wireframe)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}
}
