#ifndef HITTABLE_H
#define HITTABLE_H

#include <glm/glm.hpp>
#include "ray.h"

namespace rtiow{
    struct HitRecord{
        glm::vec3 contact;
        glm::vec3 normal;
        float t;
        bool front_face;
    };

    void set_face_normal(HitRecord* rec, const Ray& r, const glm::vec3& outward_normal);
}

#endif