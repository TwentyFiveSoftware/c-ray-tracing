#pragma once

#include "vec3.h"
#include "ray.h"

typedef struct {
    vec3 lookFrom;
    vec3 upperLeftCorner;
    vec3 horizontalDirection;
    vec3 verticalDirection;
} camera;

camera new_camera(vec3 lookFrom, vec3 lookAt, float fov, float focusDistance);

ray get_camera_ray(camera *camera, float u, float v);
