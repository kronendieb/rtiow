#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include "ray.h"

namespace rtiow{
    struct Camera{
        glm::vec3 origin;
        glm::vec3 lower_left_corner;
        glm::vec3 horizontal;
        glm::vec3 vertical;
    };

    Camera initCamera();
    Ray get_ray(Camera c, float u, float v);
}

#endif