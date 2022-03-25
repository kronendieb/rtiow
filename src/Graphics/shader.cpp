#include "shader.h"
#include <iostream>


namespace rtiow{

void loadShader(char** shader, int* length, char* path){
    FILE* f = fopen(path, "r");

    if(!f){
        std::cerr << "Could not read path: " << path << "\n";
        return;
    };

    fseek(f, 0, SEEK_END);
    *length = ftell(f);
    fseek(f, 0, SEEK_SET);

    *shader = (char*)calloc(*length, sizeof(char));
    printf("%s\n", *shader);
    if(shader){
        fread(*shader, 1, *length, f);
    }
    fclose(f);
}


Shader buildShader(char* path, ShaderType type){
    char* shaderContent = NULL;
    int shaderLength = 0;
    GLuint shaderPtr = 0;
    rtiow::loadShader(&shaderContent, &shaderLength, path);

    std::cerr << "Shader: \n" << shaderContent << "\n";

    // Compile shaders through their different types
    if(type == ShaderType::VERTEX_S){

        shaderPtr = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(shaderPtr, 1, &shaderContent, NULL);
        glCompileShader(shaderPtr);

    }else if(type == ShaderType::FRAGMENT_S){

        shaderPtr = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(shaderPtr, 1, &shaderContent, NULL);
        glCompileShader(shaderPtr);

    }else if(type == ShaderType::NULL_S){
        shaderPtr = 0;
    }

    // Check shader compile status
    GLint status;
    glGetShaderiv(shaderPtr, GL_COMPILE_STATUS, &status);

    char logBuffer[512];
    glGetShaderInfoLog(shaderPtr, 512, NULL, logBuffer);
    if(status == GL_TRUE) std::cerr << "Shader " << shaderPtr << " compiled correctly\n" << logBuffer << "\n";

    // Check buffer memory garbage collection
    if(shaderContent != NULL){
        free(shaderContent);
        shaderContent = NULL;
    }

    return shaderPtr;
}

Shader buildShaderProgram(std::vector<GLuint> shaders){

    Shader shaderProgram = glCreateProgram();
    for(auto s : shaders){
        glAttachShader(shaderProgram, s);
    }
    glLinkProgram(shaderProgram);

    for(auto s : shaders){
        glDeleteShader(s);
    }

    return shaderProgram;
}

Shader  buildShaderProgram(const char* vertexPath, const char* fragmentPath){

    std::vector<GLuint> shaders;
    GLuint vshader = rtiow::buildShader((char*)vertexPath, ShaderType::VERTEX_S);
    GLuint fshader = rtiow::buildShader((char*)fragmentPath, rtiow::ShaderType::FRAGMENT_S);

    shaders.push_back(vshader);
    shaders.push_back(fshader);

    Shader s = buildShaderProgram(shaders);

    return s;
}

void setBoolUniform(Shader shader, const char* name, bool value){
    glUniform1i(glGetUniformLocation(shader, (const GLchar*)name), (GLint)value);
}

void setFloatUniform(Shader shader, const char* name, float value){
    glUniform1i(glGetUniformLocation(shader, (const GLchar*)name), (GLint)value);
}

void setIntUniform(Shader shader, const char* name, int value){
    glUniform1f(glGetUniformLocation(shader, (const GLchar*)name), (GLfloat)value);
}

void setVec3Uniform(Shader shader, const char* name, glm::vec3 value){
    glUniform3f(glGetUniformLocation(shader, (const GLchar*) name), value.x, value.y, value.z);
}
    
}