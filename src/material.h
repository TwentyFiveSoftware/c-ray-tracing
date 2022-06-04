#pragma once

#include "vec3.h"

typedef enum {
    DIFFUSE = 0,
    METAL = 1,
    DIELECTRIC = 2,
} MATERIAL_TYPE;

typedef enum {
    SOLID = 0,
    CHECKERED = 1,
} TEXTURE_TYPE;

typedef struct {
    MATERIAL_TYPE material_type;
    TEXTURE_TYPE texture_type;
    vec3 albedo;
    vec3 albedo2;
    float refraction_index;
} material;
