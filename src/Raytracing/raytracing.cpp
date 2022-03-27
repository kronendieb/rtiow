#include "raytracing.h"

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <vector>
#include <memory>
#include <limits>
#include <cstdlib>
#include "ray.h"
#include "sphere.h"
#include "camera.h"

namespace rtiow{

    glm::vec3 sample_pixel(glm::vec3 in, int samples){
        glm::vec3 newPix = in;
        auto scale = 1.0f / samples;
        newPix.x *= scale;
        newPix.y *= scale;
        newPix.z *= scale;
        return newPix;
    }

    float random_float(){
        return rand() / (RAND_MAX + 1.0f);
    }
    
    bool hit_any(const std::vector<Sphere>& world, const Ray& r, float t_min, float t_max, HitRecord& rec){
        HitRecord temp;
        bool hit_anything = false;
        float closest = t_max;

        for(Sphere sphere : world){
            if(raycastHit(sphere, r, t_min, closest, &temp)){
                
                hit_anything = true;
                closest = temp.t;
                rec = temp;
            }
        }

        return hit_anything;
    }

    glm::vec3 ray_color(const Ray& ray, std::vector<Sphere> world){
        HitRecord rec;

        if(hit_any(world, ray, 0, std::numeric_limits<float>::infinity(), rec)){
            return 0.5f * (rec.normal + glm::vec3(1.0f, 1.0f, 1.0f));
        }

        glm::vec3 unit_direction = glm::normalize(ray.direction);
        float t = 0.5f * (unit_direction.y + 1.0f);
        return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
    }

    GLfloat* raytracingProcess(GLuint width, GLuint height, GLuint channels){
        int samples_per_pixel = 8;
        size_t resolution = width * height * channels;
        GLfloat* image = (GLfloat*)calloc(resolution, sizeof(GLfloat));

        Camera camera = initCamera();

        std::vector<Sphere> world;
        Sphere s1 = {glm::vec3(0.0f, 0.0f, -1.0f), 0.5f};
        Sphere s2 = {glm::vec3(0.0f, -100.5f, -1.0f), 100.0f};
        world.push_back(s1);
        world.push_back(s2);

        size_t count = 0;
        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                glm::vec3 pixel_color = glm::vec3(0.0f, 0.0f, 0.0f);
                for(int s = 0; s < samples_per_pixel; s++){

                    auto u = (i + random_float()) / (width - 1);
                    auto v = (j + random_float()) / (height - 1);

                    Ray r = get_ray(camera, u, v);
                    pixel_color += ray_color(r, world);
                }
                pixel_color = sample_pixel(pixel_color, samples_per_pixel);
                image[count++] = pixel_color.x;
                image[count++] = pixel_color.y;
                image[count++] = pixel_color.z;
            }
        }

        return image;
    }
}