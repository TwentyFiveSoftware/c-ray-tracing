#pragma once

#include <stdint.h>
#include "sphere.h"

typedef struct {
    sphere *spheres;
    uint32_t sphere_count;
} scene;

scene generate_scene();

hit_record ray_hit_scene(scene *scene, ray *ray, float t_min, float t_max);
