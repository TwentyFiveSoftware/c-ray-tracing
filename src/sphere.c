#include <math.h>
#include "sphere.h"

hit_record ray_hit_sphere(sphere *sphere, ray *ray, float t_min, float t_max) {
    vec3 oc = vec_sub(ray->origin, sphere->center);
    float a = vec_dot(ray->direction, ray->direction);
    float half_b = vec_dot(oc, ray->direction);
    float c = vec_dot(oc, oc) - sphere->radius * sphere->radius;
    float discriminant = half_b * half_b - a * c;

    if (discriminant < 0.0) {
        return (hit_record) {};
    }

    float sqrt_d = sqrtf(discriminant);
    float t = (-half_b - sqrt_d) / a;
    if (t < t_min || t > t_max) {
        t = (-half_b + sqrt_d) / a;

        if (t < t_min || t > t_max) {
            return (hit_record) {};
        }
    }

    vec3 point = ray_at(ray, t);
    vec3 normal = vec_div_scalar(vec_sub(point, sphere->center), sphere->radius);
    bool is_front_face = vec_dot(ray->direction, normal) < 0.0f;

    if (!is_front_face) {
        normal = vec_neg(normal);
    }

    return (hit_record) {true, t, point, normal, is_front_face, sphere->material};
}
