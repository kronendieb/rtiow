#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

namespace rtiow{

    struct Ray{
        glm::vec3 origin;
        glm::vec3 direction;
    };

    glm::vec3 posAt(Ray r, float t);
}

#endif