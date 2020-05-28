#pragma once
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

class Model
{
public:
    Model(const std::string& path)
    {
        loadModel(path);
    }
    void Draw(const Shader& shader) const;
private:
    // model data
    std::vector<Mesh> m_Meshes;
    std::string m_Directory;
    std::vector<Texture> textures_loaded;

    void loadModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        std::string typeName);
};