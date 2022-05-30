#pragma once

#include "vec3.h"
#include "hit_record.h"
#include "ray.h"

typedef struct {
    vec3 center;
    float radius;
} sphere;

hit_record ray_hit_sphere(sphere *sphere, ray *ray, float t_min, float t_max);
