#include "camera.h"
#include "constants.h"
#include <math.h>

camera new_camera(vec3 lookFrom, vec3 lookAt, float fov, float focusDistance) {
    const float aspect_ratio = ((float) WIDTH) / ((float) HEIGHT);

    float viewportHeight = tanf(fov / 360.0f * (float) M_PI) * 2.0f;
    float viewportWidth = viewportHeight * aspect_ratio;

    vec3 forward = vec_normalized(vec_sub(lookAt, lookFrom));
    vec3 right = vec_normalized(vec_cross((vec3) {0.0f, 1.0f, 0.0f}, forward));
    vec3 up = vec_normalized(vec_cross(forward, right));

    camera camera;
    camera.lookFrom = lookFrom;
    camera.horizontalDirection = vec_mul_scalar(right, viewportWidth * focusDistance);
    camera.verticalDirection = vec_mul_scalar(up, viewportHeight * focusDistance);
    camera.upperLeftCorner = vec_add(lookFrom, vec_add(
            vec_add(vec_mul_scalar(camera.horizontalDirection, -0.5f),
                    vec_mul_scalar(camera.verticalDirection, 0.5f)),
            vec_mul_scalar(forward, focusDistance)));
    return camera;
}

ray get_camera_ray(camera *camera, float u, float v) {
    vec3 target = vec_sub(vec_add(camera->upperLeftCorner, vec_mul_scalar(camera->horizontalDirection, u)),
                          vec_mul_scalar(camera->verticalDirection, v));
    return (ray) {camera->lookFrom, vec_sub(target, camera->lookFrom)};
}
