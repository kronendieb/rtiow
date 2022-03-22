#include "shader.h"
#include <iostream>


void rtiow::loadShader(char** shader, int* length, char* path){
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


GLuint rtiow::buildShader(char* path, ShaderType type){
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