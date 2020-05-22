#include "VertexBuffer.h"
#include "glad/glad.h"

VertexBuffer::VertexBuffer(float* vertices, uint32_t size)
{
	glCreateBuffers(1, &m_Handle);
	glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_Handle);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_Handle);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
