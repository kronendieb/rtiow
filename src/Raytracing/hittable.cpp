#include "hittable.h"
#include "ray.h"
#include <glm/glm.hpp>

namespace rtiow{
    void set_face_normal(HitRecord* rec, const Ray& r, const glm::vec3& outward_normal){
        rec->front_face = glm::dot(r.direction, outward_normal) < 0;
        rec->normal = rec->front_face ? outward_normal : -outward_normal;
    }
}