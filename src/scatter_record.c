#include "scatter_record.h"

scatter_record scatter_diffuse(ray *ray, hit_record *hit_record) {
    vec3 scatter_direction = vec_add(hit_record->normal, vec_random_unit_vector());

    if (is_near_zero(scatter_direction)) {
        scatter_direction = hit_record->normal;
    }

    return (scatter_record) {
            .does_scatter = true,
            .scattered_ray = {hit_record->point, scatter_direction},
            .attenuation = ((material) hit_record->material).albedo
    };
}

scatter_record scatter(ray *ray, hit_record *hit_record) {
    switch (((material) hit_record->material).material_type) {
        case DIFFUSE:
            return scatter_diffuse(ray, hit_record);
        case METAL:
            break;
        case DIELECTRIC:
            break;
    }

    return (scatter_record) {};
}
