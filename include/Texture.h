#pragma once
#include <string>
#include <stb_image.h>
#include <glad/glad.h>

class Texture
{
public:
	Texture(const std::string& path, uint32_t index);
	~Texture();

private:
	uint32_t m_Handle;
};

