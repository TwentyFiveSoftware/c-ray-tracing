#include "image.h"
#include "constants.h"
#include "vec3.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

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

    pthread_mutex_t next_row_lock;
    uint32_t next_row = 0;
    if (pthread_mutex_init(&next_row_lock, NULL) != 0) {
        return 1;
    }

    thread_args *arg = malloc(sizeof(thread_args));
    *arg = (thread_args) {&next_row_lock, &next_row, pixels, &camera, &scene};

    pthread_t *threads = calloc(RENDER_THREADS, sizeof(pthread_t));

    struct timeval render_start_time;
    gettimeofday(&render_start_time, 0);


    for (uint32_t i = 0; i < RENDER_THREADS; ++i) {
        pthread_create(&threads[i], NULL, &render_thread, arg);
    }

    for (uint32_t i = 0; i < RENDER_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }


    struct timeval render_end_time;
    gettimeofday(&render_end_time, 0);

    int64_t elapsed_render_time = (render_end_time.tv_sec - render_start_time.tv_sec) * 1000 +
                                  (render_end_time.tv_usec - render_start_time.tv_usec) / 1000;
    printf("rendered %d samples/pixel with %d threads in %ld ms\n", SAMPLES_PER_PIXEL, RENDER_THREADS,
           elapsed_render_time);


    save_image_as_png("render.png", pixels);

    free(pixels);
    free(scene.spheres);
    free(threads);
    pthread_mutex_destroy(&next_row_lock);
    return 0;
}
