#include "renderer.h"
#include "scatter_record.h"
#include "constants.h"
#include "utils.h"
#include <math.h>
#include <stdio.h>
#include <pthread.h>

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

void render_row(uint32_t y, rgb *pixels, camera *camera, scene *scene) {
    for (uint32_t x = 0; x < WIDTH; ++x) {
        vec3 color = (vec3) {};

        for (uint32_t sample = 0; sample < SAMPLES_PER_PIXEL; ++sample) {
            float u = ((float) x + random_float()) / ((float) (WIDTH - 1));
            float v = ((float) y + random_float()) / ((float) (HEIGHT - 1));

            ray ray = get_camera_ray(camera, u, v);
            vec3 sample_color = calculate_ray_color(scene, &ray, MAX_RAY_TRACE_DEPTH);
            color = vec_add(color, sample_color);
        }

        color = vec_div_scalar(color, (float) SAMPLES_PER_PIXEL);
        pixels[y * WIDTH + x] = color_to_rgb(color);
    }
}

void *render_thread(void *arg) {
    thread_args args = *((thread_args *) arg);

    while (true) {
        pthread_mutex_lock(args.next_row_lock);
        uint32_t y = *args.next_row;
        *args.next_row = y + 1;
        pthread_mutex_unlock(args.next_row_lock);

        if (y >= HEIGHT) {
            return NULL;
        }

        printf("%d / %d (%.2f%%)\n", y + 1, HEIGHT, ((float) (y + 1) * 100.0f) / (float) HEIGHT);
        render_row(y, args.pixels, args.camera, args.scene);
    }
}
