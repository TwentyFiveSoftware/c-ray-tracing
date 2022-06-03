#include "vec3.h"
#include "utils.h"
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

vec3 vec_random_unit_vector() {
    while (true) {
        vec3 vector = (vec3) {
                random_float() * 2.0f - 1.0f,
                random_float() * 2.0f - 1.0f,
                random_float() * 2.0f - 1.0f
        };

        if (vec_dot(vector, vector) < 1.0) {
            return vec_normalized(vector);
        }
    }
}

bool is_near_zero(vec3 a) {
    const float epsilon = 1e-8f;
    return fabsf(a.x) < epsilon && fabsf(a.y) < epsilon && fabsf(a.z) < epsilon;
}
