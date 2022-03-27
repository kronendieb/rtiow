#include "sphere.h"

#include <glm/gtx/norm.hpp>

namespace rtiow{
    bool raycastHit(Sphere s, const Ray& r, float t_min, float t_max, HitRecord* rec){
        glm::vec3 oc = r.origin - s.center;
        
        float a = glm::length2(r.direction);
        float half_b = glm::dot(oc, r.direction);
        float c = glm::length2(oc) - s.radius * s.radius;

        float discriminant = half_b * half_b - a * c;
        if(discriminant < 0) return false;
        float sqrtd = glm::sqrt(discriminant);

        float root = (-half_b - sqrtd) / a;
        if(root < t_min || t_max < root){
            root = (-half_b + sqrtd) / a;
            if(root < t_min || t_max < root) return false;
        }

        rec->t = root;
        rec->contact = posAt(r, rec->t);
        glm::vec3 outward = (rec->contact - s.center) / s.radius;
        set_face_normal(rec, r, outward);

        return true;
    }
}