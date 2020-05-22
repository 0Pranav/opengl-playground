#pragma once
#include <cstdint>

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind();
	void Unbind();
private:
	uint32_t m_Handle;
};