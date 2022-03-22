#ifndef APP_H
#define APP_H

#define APP_WIDTH 640
#define APP_NAME "Hello World"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

bool initApp();

void getTextures();
void renderTriangle();

void drawTriangle();

#endif