#include "app.h"
#include "window.h"
#include "shader.h"
#include <iostream>
#include <functional>

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
    //renderTriangle(&vao, &vbo);
    renderRectangle(&vao, &vbo, &ebo);

    // Create shader and get the shader ID
    Shader shaderProgram = buildShaderProgram("./assets/shaders/vshader.glsl", "./assets/shaders/fshader.glsl");

    glUseProgram(shaderProgram);

    glBindFragDataLocation(shaderProgram, 0, "outColor");

    setVec3Uniform(shaderProgram, "inColor", glm::vec3(1.0f, 0.0f, 0.0f));
    
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);

    GLuint err = glGetError();
    err != 0 ? printf("Error: %d\n", err) : printf("there is no error\n");

    RenderAction rectangle = {drawRectangle, shaderProgram, vao};
    RenderAction wireframe = {[]{ // Set glPoligonMode to wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }, shaderProgram, vao};

    // Create buffers and add the action to draw
    addAction(rectangle);
    addAction(wireframe);

    runWindow(defaultWindow);

    glDeleteProgram(shaderProgram);

    glDeleteBuffers(1, &vbo);

    glDeleteVertexArrays(1, &vao);

    closeWindow();

    return defaultWindow != nullptr;
}

void renderTriangle(GLuint *vao, GLuint *vbo){
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    printf("VAO: %d\n", *vao);

    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

}

void renderRectangle(GLuint *vao, GLuint *vbo, GLuint *ebo){
    float vertices[] = {
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };
    unsigned int indeces[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);

    printf("VAO: %d\n", *vao);

    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indeces), indeces, GL_STATIC_DRAW);
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