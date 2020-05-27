#pragma once

#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    Vertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec2& texCoords)
    {
        Position = pos;
        Normal = normal;
        TexCoords = texCoords;
    }
    Vertex() {}
};