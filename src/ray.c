#include "ray.h"

vec3 ray_at(ray *ray, float t) {
    return vec_add(ray->origin, vec_mul_scalar(ray->direction, t));
}
