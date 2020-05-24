#include "VertexArray.h"
#include <glad/glad.h>

VertexArray::VertexArray()
{
	glCreateVertexArrays(1, &m_Handle);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_Handle);
}

void VertexArray::AddBuffer(std::shared_ptr<VertexBuffer> buffer)
{
	this->Bind();
	buffer->Bind();

	auto layout = buffer->GetLayout();
	uint32_t index = 0;
	for (const auto& element : layout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, element.Count, GL_FLOAT, GL_FALSE, layout.GetStride(), (const void*)element.Offset);
		index++;
	}
	m_VertexBuffers.push_back(buffer);
}

void VertexArray::SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer)
{
	this->Bind();
	indexBuffer->Bind();
	m_IndexBuffer = indexBuffer;
}

void VertexArray::Bind()
{
	glBindVertexArray(m_Handle);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

void VertexArray::DrawArray()
{
	this->Bind();
	for (auto buffer : m_VertexBuffers) 
		glDrawArrays(GL_TRIANGLES, 0, buffer->GetCount());
	this->Unbind();
}

void VertexArray::DrawIndexed()
{
}
