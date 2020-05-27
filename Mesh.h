#pragma once
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

struct Vertex
{
	glm::vec3 postition;
	glm::vec3 normal;
	glm::vec2 texCoords;

};
class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
private:
	std::vector<Vertex> m_Vertices;
	std::vector<uint32_t> m_Indices;
	

	const std::shared_ptr<VertexArray> m_VertexArray;
	const std::shared_ptr<Shader> m_Shader;
	const std::shared_ptr<Texture> m_Texture;
};

