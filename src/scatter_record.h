#pragma once

#include <stdbool.h>
#include "vec3.h"
#include "ray.h"
#include "hit_record.h"

typedef struct {
    bool does_scatter;
    vec3 attenuation;
    ray scattered_ray;
} scatter_record;

scatter_record scatter(ray *ray, hit_record *hit_record);
