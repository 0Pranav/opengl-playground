#pragma once
#include <cstdint>
#include <string>

class VertexBuffer
{
public:
	VertexBuffer(float* vertices, uint32_t size);
	~VertexBuffer();
	void Bind();
	void Unbind();
private:
	uint32_t m_Handle;
};

