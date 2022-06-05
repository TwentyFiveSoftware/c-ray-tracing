#pragma once

#include "vec3.h"

typedef struct {
    vec3 origin;
    vec3 direction;
} ray;

inline vec3 ray_at(ray *ray, float t) {
    return vec_add(ray->origin, vec_mul_scalar(ray->direction, t));
}
