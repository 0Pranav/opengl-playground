#pragma once
#include <Texture.h>
#include <Shader.h>
#include <VertexArray.h>


struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh {
public:
    // mesh data
    std::vector<Vertex>       m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<Texture>      m_Textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader shader);
private:
    //  render data
    std::unique_ptr<VertexArray> m_VAO;

    void setupMesh();
};