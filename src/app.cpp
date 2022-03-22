
#include "app.h"
#include "window.h"
#include "shader.h"
#include <iostream>


bool initApp(){
    double aspect_ratio = 16.0 / 9.0;
    int width = APP_WIDTH, height = (float (width) / aspect_ratio);
    char* appName = APP_NAME;

    // Create the window, assigned to the defaultWindow
    printf("Width: %d, Height: %d\n", width, height);
    rtiow::defaultWindow = rtiow::initWindow(&width, &height, appName);
    glfwMakeContextCurrent(rtiow::defaultWindow);

    float vertices[] = {
        0.0f, 0.5f,
        0.5f, -0.5f,
        -0.5f, -0.5f
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    printf("VAO: %d\n", vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Build the shaders
    GLuint vshader = rtiow::buildShader("./assets/shaders/vshader.glsl", rtiow::ShaderType::VERTEX_S);
    GLuint fshader = rtiow::buildShader("./assets/shaders/fshader.glsl", rtiow::ShaderType::FRAGMENT_S);

    // Create the shader programs
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vshader);
    glAttachShader(shaderProgram, fshader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);

    GLuint err = glGetError();
    err != 0 ? printf("Error: %d\n", err) : printf("there is no error\n");

    // Create buffers and add the action to draw
    rtiow::addAction(drawTriangle);

    rtiow::runWindow(rtiow::defaultWindow);

    glDeleteProgram(shaderProgram);
    glDeleteShader(vshader);
    glDeleteShader(fshader);

    glDeleteBuffers(1, &vbo);

    glDeleteVertexArrays(1, &vao);

    rtiow::closeWindow();

    return rtiow::defaultWindow != nullptr ? true : false;
}

void renderTriangle(){
}

void drawTriangle(){
    glDrawArrays(GL_TRIANGLES, 0, 3);
}