#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    this->m_Vertices = vertices;
    this->m_Indices = indices;
    this->m_Textures = textures;

    setupMesh();
}

void Mesh::Draw(Shader shader)
{
    uint32_t diffuseNr = 1;
    uint32_t specularNr = 1;

    for (uint32_t i = 0; i < m_Textures.size(); i++)
    {
        std::string number;
        std::string name = m_Textures[i].GetType();
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);

        shader.SetInt(("material." + name + number).c_str(), i);
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, m_Textures[i].GetID());

        m_VAO->DrawIndexed();
    }
}

void Mesh::setupMesh()
{
    m_VAO.reset(new VertexArray());
    m_VAO->Bind();
    std::shared_ptr<VertexBuffer> vbo;
    auto vertexFloatVector = VertexToFloat(m_Vertices);
    vbo.reset(new VertexBuffer(&vertexFloatVector[0], m_Vertices.size() * sizeof(Vertex)));
    BufferLayout meshBufferLayout = {
        BufferElement("position",3),
        BufferElement("normal",3),
        BufferElement("texCoords", 2)
    };
    vbo->SetLayout(meshBufferLayout);
    m_VAO->AddBuffer(vbo);

    std::shared_ptr<IndexBuffer> ebo;
    ebo.reset(new IndexBuffer(&m_Indices[0], m_Indices.size() * sizeof(uint32_t)));
}

std::vector<float> VertexToFloat(std::vector<Vertex> vertices)
{
    std::vector<float> result;
    for (auto vertex : vertices)
    {
        result.push_back(vertex.Position.x);
        result.push_back(vertex.Position.y);
        result.push_back(vertex.Position.z);
        result.push_back(vertex.Normal.x);
        result.push_back(vertex.Normal.y);
        result.push_back(vertex.Normal.z);
        result.push_back(vertex.TexCoords.x);
        result.push_back(vertex.TexCoords.y);
    }
    return result;
}