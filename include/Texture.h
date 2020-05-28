#pragma once
#include <string>
#include <stb_image.h>
#include <glad/glad.h>

class Texture
{
public:
	Texture(const std::string& path);
	~Texture();

	const std::string GetType() const { return m_Type; };
	void SetType(const std::string& type) { m_Type = type; }
	void SetPath(const std::string& path) { m_Path = path; }
	const uint32_t GetID() const { return m_Handle; };
	const std::string GetPath() const { return m_Path; };

	void Bind(unsigned int slot = 0 );
	void Unbind();

private:
	uint32_t m_Handle;
	std::string m_Type;
	std::string m_Path;
};

