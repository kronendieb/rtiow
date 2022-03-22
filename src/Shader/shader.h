#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace rtiow{
    enum ShaderType {
        NULL_S, VERTEX_S, FRAGMENT_S
    };
    void loadShader(char** shader, int* length, char* path);

    GLuint buildShader(char* path, ShaderType type);
}

#endif