#include "app.h"
#include "window.h"
#include "shader.h"
#include <iostream>
#include <functional>
#include <stdlib.h>

namespace rtiow{

bool initApp(){
    double aspect_ratio = 16.0 / 9.0;
    int width = APP_WIDTH, height = (float (width) / aspect_ratio);
    char* appName = APP_NAME;

    // Create the window, assigned to the defaultWindow
    printf("Width: %d, Height: %d\n", width, height);
    defaultWindow = initWindow(&width, &height, appName);
    glfwMakeContextCurrent(defaultWindow);

    // Create buffers and buffer objects
    GLuint vao, vbo, ebo, tex;
    //renderTriangle(&vao, &vbo);
    renderRectangle(&vao, &vbo, &ebo, &tex);

    // Create shader and get the shader ID
    Shader shaderProgram = buildShaderProgram("./assets/shaders/vshader.glsl", "./assets/shaders/fshader.glsl");

    glUseProgram(shaderProgram);

    glBindFragDataLocation(shaderProgram, 0, "FragDataColor");

    //setVec3Uniform(shaderProgram, "inColor", glm::vec3(1.0f, 0.0f, 0.0f));
    
    GLint posAttrib = glGetAttribLocation(shaderProgram, "m_position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "m_color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

    GLint texCoordAttrib = glGetAttribLocation(shaderProgram, "m_texCoord");
    glEnableVertexAttribArray(texCoordAttrib);
    glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));


    GLuint err = glGetError();
    err != 0 ? printf("Error: %d\n", err) : printf("there is no error\n");

    RenderAction rectangle = {drawRectangle, shaderProgram, vao, tex};

    RenderAction wireframe = {[]{ // Set glPoligonMode to wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }, shaderProgram, vao};

    // Create buffers and add the action to draw
    addAction(rectangle);
    //addAction(wireframe);

    runWindow(defaultWindow);

    glDeleteProgram(shaderProgram);

    glDeleteBuffers(1, &vbo);

    glDeleteVertexArrays(1, &vao);

    closeWindow();

    return defaultWindow != nullptr;
}

void renderTriangle(GLuint *vao, GLuint *vbo){
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    printf("VAO: %d\n", *vao);

    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

}

void renderRectangle(GLuint *vao, GLuint *vbo, GLuint *ebo, GLuint *tex){
    float vertices[] = {
         1.0f,  1.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, /**/ 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, /**/ 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, /**/ 0.0f, 0.0f,
         1.0f, -1.0f, 0.0f, /**/ 1.0f, 1.0f, 1.0f, /**/ 0.0f, 1.0f
    };
    unsigned int indeces[] = {
        0, 1, 3,
        1, 2, 3
    };

    const int width = 64;
    const int height = 64;

    int count = 0;
    size_t textureSize = width * height * 3 * sizeof(float);
    GLfloat* texture = (GLfloat*)malloc(textureSize);
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++){
            texture[count++] = (1.0f / width) * i;
            texture[count++] = (1.0f / height) * j;
            texture[count++] = 0.5f;
        }
    }


    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

    glGenTextures(1, tex);
    glBindTexture(GL_TEXTURE_2D, *tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, texture);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    free(texture);
    texture = NULL;

}

void drawTriangle(){
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void drawRectangle(){
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void setWireframeMode(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
}