#pragma once

#include "vec3.h"
#include "ray.h"
#include "image.h"
#include "scene.h"
#include "camera.h"
#include <pthread.h>

typedef struct {
    pthread_mutex_t *next_row_lock;
    uint32_t *next_row;
    rgb *pixels;
    camera *camera;
    scene *scene;
} thread_args;

void *render_thread(void *args);
