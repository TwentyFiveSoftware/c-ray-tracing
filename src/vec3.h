#pragma once

#include <stdbool.h>

typedef struct {
    float x;
    float y;
    float z;
} vec3;

inline vec3 vec_neg(vec3 a) {
    return (vec3) {-a.x, -a.y, -a.z};
}

inline vec3 vec_add(vec3 a, vec3 b) {
    return (vec3) {a.x + b.x, a.y + b.y, a.z + b.z};
}

inline vec3 vec_sub(vec3 a, vec3 b) {
    return (vec3) {a.x - b.x, a.y - b.y, a.z - b.z};
}

inline vec3 vec_mul(vec3 a, vec3 b) {
    return (vec3) {a.x * b.x, a.y * b.y, a.z * b.z};
}

inline vec3 vec_mul_scalar(vec3 a, float scalar) {
    return (vec3) {a.x * scalar, a.y * scalar, a.z * scalar};
}

inline vec3 vec_div_scalar(vec3 a, float scalar) {
    return (vec3) {a.x / scalar, a.y / scalar, a.z / scalar};
}

inline float vec_dot(const vec3 *a, const vec3 *b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

vec3 vec_cross(vec3 a, vec3 b);

float vec_length(vec3 a);

vec3 vec_normalized(vec3 a);

vec3 vec_sqrt(vec3 a);

vec3 vec_random_unit_vector();

bool vec_is_near_zero(vec3 a);

vec3 vec_reflect(vec3 a, vec3 normal);

vec3 vec_refract(vec3 a, vec3 normal, float refraction_ratio);
