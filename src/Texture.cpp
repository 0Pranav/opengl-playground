#include "Texture.h"

Texture::Texture(const std::string& path, uint32_t index)
{
	glActiveTexture(GL_TEXTURE0 + index);
	glGenTextures(1, &m_Handle);
	glBindTexture(GL_TEXTURE_2D, m_Handle);
	int texWidth, texHeight, nrChannels = 0;
	auto data = stbi_load(path.c_str(), &texWidth, &texHeight, &nrChannels, NULL);
	GLenum format;
	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3)
		format = GL_RGB;
	else if (nrChannels == 4)
		format = GL_RGBA;
	glTexImage2D(GL_TEXTURE_2D, 0, format, texWidth, texHeight, 0, format, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

Texture::~Texture()
{
}
