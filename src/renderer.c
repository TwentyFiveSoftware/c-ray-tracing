#include "renderer.h"
#include "scatter_record.h"
#include <math.h>

vec3 calculate_ray_color(scene *scene, ray *ray, int32_t depth) {
    if (depth <= 0) {
        return (vec3) {};
    }

    hit_record hit_record = ray_hit_scene(scene, ray, 0.001f, INFINITY);
    if (hit_record.hit) {
        scatter_record scatter_record = scatter(ray, &hit_record);
        if (scatter_record.does_scatter) {
            return vec_mul(scatter_record.attenuation,
                           calculate_ray_color(scene, &scatter_record.scattered_ray, depth - 1));
        }

        return (vec3) {};
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
