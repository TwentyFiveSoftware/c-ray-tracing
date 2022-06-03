#include <malloc.h>
#include "scene.h"

scene generate_scene() {
    uint32_t max_spheres = 500;

    sphere *spheres = calloc(max_spheres, sizeof(sphere));
    if (!spheres) {
        return (scene) {};
    }

    uint32_t sphere_index = 0;

    spheres[sphere_index++] = (sphere) {(vec3) {0.0f, 0.0f, -1.0f}, 0.5f,
                                        {DIFFUSE, {1.0f, 0.0f, 0.0f}}};

    return (scene) {.spheres = spheres, .sphere_count = sphere_index};
}

hit_record ray_hit_scene(scene *scene, ray *ray, float t_min, float t_max) {
    hit_record current_record = (hit_record) {.t = t_max};

    for (uint32_t i = 0; i < scene->sphere_count; ++i) {
        hit_record record = ray_hit_sphere(&scene->spheres[i], ray, t_min, current_record.t);
        if (record.hit) {
            current_record = record;
        }
    }

    return current_record;
}
