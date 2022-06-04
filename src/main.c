#include "image.h"
#include "constants.h"
#include "vec3.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main() {
    camera camera = new_camera((vec3) {12.0f, 2.0f, -3.0f}, (vec3) {}, 25.0f, 10.0f);

    scene scene = generate_scene();
    if (!scene.spheres) {
        return 1;
    }

    rgb *pixels = calloc(WIDTH * HEIGHT, sizeof(rgb));
    if (!pixels) {
        return 1;
    }

    clock_t render_start_time = clock();

    for (uint32_t y = 0; y < HEIGHT; ++y) {
        printf("%d / %d (%.2f%%)\n", y + 1, HEIGHT, ((float) (y + 1) * 100.0f) / (float) HEIGHT);

        for (uint32_t x = 0; x < WIDTH; ++x) {
            vec3 color = (vec3) {};

            for (uint32_t sample = 0; sample < SAMPLES_PER_PIXEL; ++sample) {
                float u = ((float) x + random_float()) / ((float) (WIDTH - 1));
                float v = ((float) y + random_float()) / ((float) (HEIGHT - 1));

                ray ray = get_camera_ray(&camera, u, v);
                vec3 sample_color = calculate_ray_color(&scene, &ray, MAX_RAY_TRACE_DEPTH);
                color = vec_add(color, sample_color);
            }

            color = vec_div_scalar(color, (float) SAMPLES_PER_PIXEL);
            pixels[y * WIDTH + x] = color_to_rgb(color);
        }
    }

    uint32_t elapsed_render_time = (uint32_t) (((float) (clock() - render_start_time) * 1000.0f) / CLOCKS_PER_SEC);
    printf("Rendered %d samples/pixel with %d threads in %d ms", SAMPLES_PER_PIXEL, 1, elapsed_render_time);

    save_image_as_png("render.png", pixels);

    free(pixels);
    free(scene.spheres);
    return 0;
}
