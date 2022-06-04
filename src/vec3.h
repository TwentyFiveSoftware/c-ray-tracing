#pragma once

#include <stdbool.h>

typedef struct {
    float x;
    float y;
    float z;
} vec3;

vec3 vec_neg(vec3 a);

vec3 vec_add(vec3 a, vec3 b);

vec3 vec_sub(vec3 a, vec3 b);

vec3 vec_mul(vec3 a, vec3 b);

vec3 vec_mul_scalar(vec3 a, float scalar);

vec3 vec_div_scalar(vec3 a, float scalar);

float vec_dot(vec3 *a, vec3 *b);

vec3 vec_cross(vec3 a, vec3 b);

float vec_length(vec3 a);

vec3 vec_normalized(vec3 a);

vec3 vec_sqrt(vec3 a);

vec3 vec_random_unit_vector();

bool vec_is_near_zero(vec3 a);

vec3 vec_reflect(vec3 a, vec3 normal);

vec3 vec_refract(vec3 a, vec3 normal, float refraction_ratio);
