#ifndef SPHERE_H
#define SPHERE_H

#include <glm/glm.hpp>

#include "ray.h"
#include "hittable.h"

namespace rtiow{
    struct Sphere{
        glm::vec3 center;
        float radius;
    };

    bool raycastHit(Sphere s, const Ray& r, float t_min, float t_max, HitRecord* rec);
}

#endif