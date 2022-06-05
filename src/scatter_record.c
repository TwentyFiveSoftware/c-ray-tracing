#include "scatter_record.h"
#include <math.h>

static vec3 texture_get_color(material *material, vec3 *point) {
    switch (material->texture_type) {
        case SOLID:
            return material->albedo;
        case CHECKERED: {
            float size = 6.0f;
            float sines = sinf(size * point->x) * sinf(size * point->y) * sinf(size * point->z);
            return sines < 0.0f ? material->albedo : material->albedo2;
        }
    }

    return (vec3) {};
}

static scatter_record scatter_diffuse(hit_record *hit_record) {
    vec3 scatter_direction = vec_add(hit_record->normal, vec_random_unit_vector());

    if (vec_is_near_zero(scatter_direction)) {
        scatter_direction = hit_record->normal;
    }

    return (scatter_record) {
            .does_scatter = true,
            .attenuation = texture_get_color(&hit_record->material, &hit_record->point),
            .scattered_ray = {hit_record->point, scatter_direction}
    };
}

static scatter_record scatter_metal(ray *ray, hit_record *hit_record) {
    vec3 scatter_direction = vec_reflect(vec_normalized(ray->direction), hit_record->normal);

    return (scatter_record) {
            .does_scatter = vec_dot(&scatter_direction, &hit_record->normal) > 0.0f,
            .attenuation = texture_get_color(&hit_record->material, &hit_record->point),
            .scattered_ray = {hit_record->point, scatter_direction}
    };
}

static scatter_record scatter_dielectric(ray *ray, hit_record *hit_record) {
    float refraction_ratio = hit_record->is_front_face ? 1.0f / hit_record->material.refraction_index
                                                       : hit_record->material.refraction_index;
    vec3 scatter_direction = vec_refract(vec_normalized(ray->direction), hit_record->normal, refraction_ratio);

    return (scatter_record) {
            .does_scatter = true,
            .attenuation = {1.0f, 1.0f, 1.0f},
            .scattered_ray = {hit_record->point, scatter_direction}
    };
}

scatter_record scatter(ray *ray, hit_record *hit_record) {
    switch (hit_record->material.material_type) {
        case DIFFUSE:
            return scatter_diffuse(hit_record);
        case METAL:
            return scatter_metal(ray, hit_record);
        case DIELECTRIC:
            return scatter_dielectric(ray, hit_record);
    }

    return (scatter_record) {};
}
