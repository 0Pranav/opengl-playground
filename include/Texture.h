#pragma once
#include <string>
#include <stb_image.h>
#include <glad/glad.h>

class Texture
{
public:
	Texture(const std::string& path, uint32_t index);
	~Texture();
	std::string GetType() { return m_Type; };
	uint32_t GetID() { return m_Handle; };
private:
	uint32_t m_Handle;
	std::string m_Type;
};

