#include "image.h"
#include "constants.h"
#include "vec3.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include <stdlib.h>

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

    for (uint32_t y = 0; y < HEIGHT; ++y) {
        for (uint32_t x = 0; x < WIDTH; ++x) {
            float u = ((float) x) / ((float) (WIDTH - 1));
            float v = ((float) y) / ((float) (HEIGHT - 1));

            ray ray = get_camera_ray(&camera, u, v);
            vec3 color = calculate_ray_color(&scene, &ray);
            pixels[y * WIDTH + x] = color_to_rgb(color);
        }
    }

    save_image_as_png("render.png", pixels);

    free(pixels);
    free(scene.spheres);
    return 0;
}
