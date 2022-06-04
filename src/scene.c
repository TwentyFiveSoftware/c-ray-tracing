#include <malloc.h>
#include "scene.h"

scene generate_scene() {
    uint32_t max_spheres = 500;

    sphere *spheres = calloc(max_spheres, sizeof(sphere));
    if (!spheres) {
        return (scene) {};
    }

    uint32_t sphere_index = 0;

    spheres[sphere_index++] = (sphere) {{0.0f, -1000.0f, 1.0f}, 1000.0f,
                                        {DIFFUSE, CHECKERED,
                                         {0.05f, 0.05f, 0.05f}, {0.95f, 0.95f, 0.95f}}};

    spheres[sphere_index++] = (sphere) {{0.0f, 1.0f, 0.0f}, 1.0f,
                                        {DIELECTRIC, .refraction_index = 1.5f}};

    spheres[sphere_index++] = (sphere) {{-4.0f, 1.0f, 0.0f}, 1.0f,
                                        {DIFFUSE, SOLID, {0.6f, 0.3f, 0.1f}}};

    spheres[sphere_index++] = (sphere) {{4.0f, 1.0f, 0.0f}, 1.0f,
                                        {METAL, SOLID, {0.7f, 0.6f, 0.5f}}};

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
