#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <vector>

namespace rtiow{
    enum TextureType{
        DIFFUSE_T, SPECULAR_T
    };

    struct Vertex{
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };

    struct Texture{
        GLuint id;
        TextureType type;
    };

    struct MeshData{
        std::vector<Vertex> vertices;
        std::vector<GLuint> indeces;
        std::vector<Texture> textures;

        GLuint VAO, VBO, EBO;
    };

    void setupMesh(MeshData *data);
}

#endif