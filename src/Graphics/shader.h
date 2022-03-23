#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <glm/glm.hpp>

namespace rtiow{

    using Shader = GLuint;

    enum ShaderType {
        NULL_S, VERTEX_S, FRAGMENT_S
    };

    void loadShader(char** shader, int* length, char* path);

    Shader buildShader(char* path, ShaderType type);
    Shader buildShaderProgram(std::vector<GLuint> shaders);

    /*
    *   Build a complete shader program through shader paths
    *   @return A shader id as GLuint
    *   @param vertexPath The path to the vertex shader from start
    *   @param fragmentPath The path to the framgent shader from start
    */
    Shader buildShaderProgram(const char* vertexPath, const char* fragmentPath);

    void useShader(Shader toUse);

    void setBoolUniform(Shader shader, const char* name, bool value);
    void setFloatUniform(Shader shader, const char* name, float value);
    void setIntUniform(Shader shader, const char* name, int value);
    void setVec3Uniform(Shader shader, const char* name, glm::vec3 value);
}

#endif