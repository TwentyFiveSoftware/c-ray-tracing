#pragma once

#include <stdbool.h>
#include "vec3.h"

typedef struct {
    bool hit;
    float t;
    vec3 point;
    vec3 normal;
    bool is_front_face;
} hit_record;
