#include "renderer.h"

vec3 calculate_ray_color(ray *ray) {
    const float t = 0.5f * (vec_normalized(ray->direction).y + 1.0f);
    return vec_add(vec_mul_scalar((vec3) {1.0f, 1.0f, 1.0f}, 1.0f - t),
                   vec_mul_scalar((vec3) {0.5f, 0.7f, 1.0f}, t));
}

rgb color_to_rgb(vec3 color) {
    color = vec_sqrt(color);
    color = vec_mul_scalar(color, 0xFF);

    return (rgb) {(uint8_t) color.x, (uint8_t) color.y, (uint8_t) color.z};
}
