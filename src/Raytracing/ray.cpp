#include "ray.h"

namespace rtiow{
    glm::vec3 posAt(Ray r, float t){
        return r.origin + t * r.direction;
    }
}