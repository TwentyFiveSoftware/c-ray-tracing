#pragma once

#include "vec3.h"
#include "ray.h"
#include "image.h"
#include "scene.h"

vec3 calculate_ray_color(scene *scene, ray *ray);

rgb color_to_rgb(vec3 color);
