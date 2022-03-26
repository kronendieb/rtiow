#include "raytracing.h"

#include <glm/glm.hpp>
#include "ray.h"

namespace rtiow{
    
    bool hit_sphere(const glm::vec3& center, float radius, const Ray& ray){
        glm::vec3 oc = ray.origin - center;
        auto a = glm::dot(ray.direction, ray.direction);
        auto b = 2.0f * glm::dot(oc, ray.direction);
        auto c = glm::dot(oc, oc) - radius * radius;
        auto discriminant = b * b - 4 * a * c;
        return discriminant > 0;
    }

    glm::vec3 ray_color(const Ray& ray){
        if(hit_sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f, ray))
            return glm::vec3(1.0f, 0.5f, 0.5f);
        glm::vec3 unit_direction = glm::normalize(ray.direction);
        auto t = 0.5f * (unit_direction.y + 1.0f);
        return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
    }

    GLfloat* raytracingProcess(GLuint width, GLuint height, GLuint channels){
        size_t resolution = width * height * channels;
        GLfloat* image = (GLfloat*)calloc(resolution, sizeof(GLfloat));

        GLfloat vp_height = 2.0f; // the height of the viewport through camera
        GLfloat vp_width = (16.0f / 9.0f) * vp_height; // the width of the viewport
        GLfloat focal_length = 1.0f;

        glm::vec3 origin = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 horizontal = glm::vec3(vp_width, 0.0f, 0.0f);
        glm::vec3 vertical = glm::vec3(0.0f, vp_height, 0.0f);
        glm::vec3 lower_left_corner = origin - horizontal / 2.0f - vertical / 2.0f - glm::vec3(0.0f, 0.0f, focal_length);

        size_t count = 0;
        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                auto u = float(i) / width;
                auto v = float(j) / height;

                Ray r = {origin, lower_left_corner + u * horizontal + v * vertical - origin};
                glm::vec3 pixel_color = ray_color(r);

                image[count++] = pixel_color.x;
                image[count++] = pixel_color.y;
                image[count++] = pixel_color.z;
            }
        }

        return image;
    }
}