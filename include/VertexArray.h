#pragma once
#include <cstdint>
#include <memory>
#include <VertexBuffer.h>

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(std::shared_ptr<VertexBuffer> buffer);
	void SetIndexBuffer(std::shared_ptr<IndexBuffer> indexBuffer);

	void Bind();
	void Unbind();

	void DrawArray();
	void DrawIndexed();
private:
	uint32_t m_Handle;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
};