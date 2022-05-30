#include "renderer.h"
#include <math.h>

vec3 calculate_ray_color(scene *scene, ray *ray) {
    hit_record hit_record = ray_hit_scene(scene, ray, 0.001f, INFINITY);
    if (hit_record.hit) {
        return vec_mul_scalar(vec_add(hit_record.normal, (vec3) {1.0f, 1.0f, 1.0f}), 0.5f);
    }

    const float t = 0.5f * (vec_normalized(ray->direction).y + 1.0f);
    return vec_add(vec_mul_scalar((vec3) {1.0f, 1.0f, 1.0f}, 1.0f - t),
                   vec_mul_scalar((vec3) {0.5f, 0.7f, 1.0f}, t));
}

rgb color_to_rgb(vec3 color) {
    color = vec_sqrt(color);
    color = vec_mul_scalar(color, 0xFF);

    return (rgb) {(uint8_t) color.x, (uint8_t) color.y, (uint8_t) color.z};
}
