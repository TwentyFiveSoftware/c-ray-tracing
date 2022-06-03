#pragma once

#include "vec3.h"

typedef enum {
    DIFFUSE = 0,
    METAL = 1,
    DIELECTRIC = 2,
} MATERIAL_TYPE;

typedef struct {
    MATERIAL_TYPE material_type;
    vec3 albedo;
    float refraction_index;
} material;
