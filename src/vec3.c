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

vec3 vec_div_scalar(vec3 a, float scalar) {
    return (vec3) {a.x / scalar, a.y / scalar, a.z / scalar};
}

float vec_dot(vec3 *a, vec3 *b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

vec3 vec_cross(vec3 a, vec3 b) {
    return (vec3) {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x,
    };
}

float vec_length(vec3 a) {
    return sqrtf(vec_dot(&a, &a));
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

        if (vec_dot(&vector, &vector) < 1.0) {
            return vec_normalized(vector);
        }
    }
}

bool vec_is_near_zero(vec3 a) {
    const float epsilon = 1e-8f;
    return fabsf(a.x) < epsilon && fabsf(a.y) < epsilon && fabsf(a.z) < epsilon;
}

vec3 vec_reflect(vec3 a, vec3 normal) {
    return vec_sub(a, vec_mul_scalar(normal, 2.0f * vec_dot(&a, &normal)));
}

vec3 vec_refract(vec3 a, vec3 normal, float refraction_ratio) {
    vec3 minus_a = vec_neg(a);
    float cos_theta = fminf(vec_dot(&normal, &minus_a), 1.0f);
    float sin_theta = sqrtf(1.0f - cos_theta * cos_theta);

    float r0 = (1.0f - refraction_ratio) / (1.0f + refraction_ratio);
    float reflectance = r0 * r0 + (1.0f - r0 * r0) * powf(1.0f - cos_theta, 5.0f);

    if (refraction_ratio * sin_theta > 1.0f || reflectance > random_float()) {
        return vec_reflect(a, normal);
    }

    vec3 r_out_perpendicular = vec_mul_scalar(vec_add(a, vec_mul_scalar(normal, cos_theta)), refraction_ratio);
    vec3 r_out_parallel = vec_mul_scalar(normal,
                                         -sqrtf(fabsf(1.0f - vec_dot(&r_out_perpendicular, &r_out_perpendicular))));
    return vec_add(r_out_perpendicular, r_out_parallel);
}
