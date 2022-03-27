#include "texture.h"

#include <iostream>

namespace rtiow{

    void generateTexture(Texture* t){
        glGenTextures(1, &(*t).m_textureID);
        glBindTexture(GL_TEXTURE_2D, t->m_textureID);
        printf("Texture binding: %d\n", t->m_textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t->m_width, t->m_height, 0, GL_RGB, GL_FLOAT, t->m_data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void bindTexture(Texture* t){
        glBindTexture(GL_TEXTURE_2D, t->m_textureID);
    }

    void freeTexture(Texture* t){
        if(t->m_data == NULL) return;
        free(t->m_data);
        t->m_data = NULL;
    }
}