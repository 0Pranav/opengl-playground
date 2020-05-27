#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    this->m_Vertices = vertices;
    this->m_Indices = indices;
    this->m_Textures = textures;

    setupMesh();
}

void Mesh::Draw() const
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for (unsigned int i = 0; i < m_Textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = m_Textures[i].GetType();
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);

        //shader.SetInt((name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, m_Textures[i].GetID());
    }
    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    m_VAO->DrawIndexed();
}

void Mesh::setupMesh()
{
    m_VAO.reset(new VertexArray());
    m_VAO->Bind();
    std::shared_ptr<VertexBuffer> vbo;
    vbo.reset(new VertexBuffer(&m_Vertices[0], m_Vertices.size() * sizeof(Vertex)));
    BufferLayout meshBufferLayout = {
        BufferElement("position", 3),
        BufferElement("normal", 3),
        BufferElement("texCoords", 2)
    };
    vbo->SetLayout(meshBufferLayout);
    m_VAO->AddBuffer(vbo);

    std::shared_ptr<IndexBuffer> ebo;
    ebo.reset(new IndexBuffer(&m_Indices[0], m_Indices.size()));
    m_VAO->SetIndexBuffer(ebo);
}