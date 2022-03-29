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

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		ST_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(m_VertexBufferIndex);
			glVertexAttribPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataToGL(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(intptr_t)element.Offset);
			m_VertexBufferIndex++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}
