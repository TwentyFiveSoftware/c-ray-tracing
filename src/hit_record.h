#pragma once

#include <stdbool.h>
#include "vec3.h"
#include "material.h"

typedef struct {
    bool hit;
    float t;
    vec3 point;
    vec3 normal;
    bool is_front_face;
    material material;
} hit_record;
