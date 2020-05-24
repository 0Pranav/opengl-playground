#pragma once
#include <cstdint>
#include <string>
#include <vector>

struct BufferElement
{
	uint32_t Offset;
	uint32_t Size;
	uint32_t Count;
	std::string Name;
	BufferElement(const std::string& name, uint32_t count):
		Name(name),
		Count(count),
		Size(count * 4),
		Offset(0)
	{
	};
};

class BufferLayout
{
public:
	BufferLayout() {};
	BufferLayout(const std::initializer_list<BufferElement>& elements) :
		m_Elements(elements)
	{
		CalculateOffsetsAndSize();
	}

	inline std::vector<BufferElement> GetBufferElements() const { return m_Elements; };

	std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
	std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
	std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
	std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	uint32_t GetStride() const
	{
		return m_Stride;
	}

private:
	uint32_t m_Stride = 0;
	std::vector<BufferElement> m_Elements;
	void CalculateOffsetsAndSize()
	{
		uint32_t offset = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
		}
		m_Stride = offset;
	}
};

class VertexBuffer
{
public:
	VertexBuffer(float* vertices, uint32_t size);
	~VertexBuffer();
	const BufferLayout& GetLayout() const;
	void SetLayout(const BufferLayout& layout);

	inline uint32_t GetSize() const { return m_Size;  };
	inline uint32_t GetCount() const { return GetSize() / m_Layout.GetStride(); };
	void Bind() const;
	void Unbind() const;
private:
	uint32_t m_Handle;
	BufferLayout m_Layout;
	uint32_t m_Size;
};

class IndexBuffer
{
public:
	IndexBuffer(uint32_t* indices, uint32_t count);
	~IndexBuffer();

	void Bind() const ;
	void Unbind() const ;

	virtual uint32_t GetCount() const { return m_Count; };
private:
	uint32_t m_RendererID = 0;
	uint32_t m_Count = 0;
};
