#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace rtiow{
    struct Texture{
        GLuint m_textureID;
        GLuint m_width;
        GLuint m_height;
        GLfloat* m_data;
        size_t m_textureSize;
    };

    void initTexture(Texture* t, GLfloat* image, GLuint width, GLuint height, GLuint channels);
    void generateTexture(Texture* t);
    void bindTexture(Texture* t);
    void freeTexture(Texture* t);
}

#endif