#ifndef APP_H
#define APP_H

#define APP_WIDTH 640
#define APP_NAME "Hello World"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "texture.h"

namespace rtiow{

bool initApp();

void getTextures();
void renderTriangle(GLuint* vao, GLuint* vbo);
void renderRectangle(GLuint *vao, GLuint *vbo, GLuint *ebo, Texture *tex);

void drawTriangle();
void drawRectangle();
void setWireframeMode();

}
#endif