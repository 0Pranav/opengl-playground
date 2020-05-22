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

void VertexArray::Bind()
{
	glBindVertexArray(m_Handle);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}
