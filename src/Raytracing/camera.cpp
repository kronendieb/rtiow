#include "camera.h"

#include <GLFW/glfw3.h>

namespace rtiow{

    Camera initCamera(){
        GLfloat vp_height = 2.0f; // the height of the viewport through camera
        GLfloat vp_width = (16.0f / 9.0f) * vp_height; // the width of the viewport
        GLfloat focal_length = 1.0f;

        Camera c;

        c.origin = glm::vec3(0.0f, 0.0f, 0.0f);
        c.horizontal = glm::vec3(vp_width, 0.0f, 0.0f);
        c.vertical = glm::vec3(0.0f, vp_height, 0.0f);
        c.lower_left_corner = c.origin - c.horizontal / 2.0f - c.vertical / 2.0f - glm::vec3(0.0f, 0.0f, focal_length);

        return c;
    }

    Ray get_ray(Camera c, float u, float v){
        Ray r = {c.origin, c.lower_left_corner + u * c.horizontal + v * c.vertical - c.origin};
        return r;
    }

}