#include "vec3.h"
#include <math.h>

vec3 vec_neg(vec3 a) {
    return (vec3) {-a.x, -a.y, -a.z};
}

vec3 vec_add(vec3 a, vec3 b) {
    return (vec3) {a.x + b.x, a.y + b.y, a.z + b.z};
}

vec3 vec_sub(vec3 a, vec3 b) {
    return (vec3) {a.x - b.x, a.y - b.y, a.z - b.z};
}

vec3 vec_mul(vec3 a, vec3 b) {
    return (vec3) {a.x * b.x, a.y * b.y, a.z * b.z};
}

vec3 vec_mul_scalar(vec3 a, float scalar) {
    return (vec3) {a.x * scalar, a.y * scalar, a.z * scalar};
}

vec3 vec_div(vec3 a, vec3 b) {
    return (vec3) {a.x / b.x, a.y / b.y, a.z / b.z};
}

vec3 vec_div_scalar(vec3 a, float scalar) {
    return vec_mul_scalar(a, 1.0f / scalar);
}

float vec_dot(vec3 a, vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec3 vec_cross(vec3 a, vec3 b) {
    return (vec3) {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x,
    };
}

float vec_length(vec3 a) {
    return sqrtf(vec_dot(a, a));
}

vec3 vec_normalized(vec3 a) {
    return vec_div_scalar(a, vec_length(a));
}

vec3 vec_sqrt(vec3 a) {
    return (vec3) {sqrtf(a.x), sqrtf(a.y), sqrtf(a.z)};
}
