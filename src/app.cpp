#include "app.h"
#include "window.h"
#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

bool initApp(){
    double aspect_ratio = 16.0 / 9.0;
    int width = APP_WIDTH, height = (float (width) / aspect_ratio);
    char* appName = APP_NAME;

    glewExperimental = GL_TRUE;
    glewInit();

    printf("Width: %d, Height: %d\n", width, height);
    rtiow::defaultWindow = rtiow::initWindow(&width, &height, appName);

    renderTriangle();

    rtiow::runWindow(rtiow::defaultWindow);

    return rtiow::defaultWindow != nullptr ? true : false;
}

void renderTriangle(){
    float vertices[] = {
        0.0f, 0.5f,
        0.5f, -0.5f,
        -0.5f, 0.5f
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    printf("%u\n", vbo);
}