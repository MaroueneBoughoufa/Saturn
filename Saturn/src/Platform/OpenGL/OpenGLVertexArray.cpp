#include "stpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Saturn
{
	static GLenum ShaderDataToGL(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:   return GL_FLOAT;
			case ShaderDataType::Vec2f:   return GL_FLOAT;
			case ShaderDataType::Vec3f:   return GL_FLOAT;
			case ShaderDataType::Vec4f:   return GL_FLOAT;
			case ShaderDataType::Int:     return GL_INT;
			case ShaderDataType::Vec2i:   return GL_INT;
			case ShaderDataType::Vec3i:   return GL_INT;
			case ShaderDataType::Vec4i:   return GL_INT;
			case ShaderDataType::Mat3f:   return GL_FLOAT;
			case ShaderDataType::Mat4f:   return GL_FLOAT;
			case ShaderDataType::Bool:    return GL_BOOL;
		}

		ST_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				ShaderDataToGL(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}