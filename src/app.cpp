#include "app.h"

#include <iostream>
#include <functional>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#include "window.h"
#include "shader.h"
#include "texture.h"
#include "ray.h"
#include "raytracing.h"

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
    GLuint vao, vbo, ebo;
    Texture tex;
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

    RenderAction rectangle = {drawRectangle, shaderProgram, vao, tex.m_textureID};

    RenderAction wireframe = {[]{ // Set glPoligonMode to wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }, shaderProgram, vao, tex.m_textureID};

    // Create buffers and add the action to draw
    addAction(rectangle);
    //addAction(wireframe);

    runWindow(defaultWindow);

    glDeleteProgram(shaderProgram);

    glDeleteBuffers(1, &vbo);

    glDeleteVertexArrays(1, &vao);

    closeWindow();

    _CrtDumpMemoryLeaks();
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

void renderRectangle(GLuint *vao, GLuint *vbo, GLuint *ebo, Texture *tex){
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

    const GLuint width = 256;
    const GLuint height = 256;
    const GLuint channels = 3;

    tex->m_width = width;
    tex->m_height = height;
    tex->m_textureSize = width * height * channels;
    tex->m_data = raytracingProcess(width, height, channels); // Run the process of raytracing on the image

    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);

    generateTexture(tex);
    bindTexture(tex);
    freeTexture(tex);

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