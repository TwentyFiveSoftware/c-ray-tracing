#include "utils.h"
#include <math.h>
#include <stdint.h>

uint32_t random_seed = 25;

inline float random_float() {
//    return (float) rand() / (float) RAND_MAX;
    random_seed = (214013 * random_seed + 2531011);
    return (float) ((random_seed >> 16) & 0x7FFF) / 0x7FFF;
}

vec3 hsv_to_rgb(float h, float s, float v) {
    float c = s * v;
    float x = c * (1.0f - fabsf(fmodf(h / 60.0f, 2.0f) - 1.0f));
    float m = v - c;

    float r;
    float g;
    float b;

    if (h >= 0.0f && h < 60.0f) {
        r = c;
        g = x;
        b = 0.0f;
    } else if (h >= 60.0f && h < 120.0f) {
        r = x;
        g = c;
        b = 0.0f;
    } else if (h >= 120.0f && h < 180.0f) {
        r = 0.0f;
        g = c;
        b = x;
    } else if (h >= 180.0f && h < 240.0f) {
        r = 0.0f;
        g = x;
        b = c;
    } else if (h >= 240.0f && h < 300.0f) {
        r = x;
        g = 0.0f;
        b = c;
    } else {
        r = c;
        g = 0.0f;
        b = x;
    }

    return (vec3) {r + m, g + m, b + m};
}

vec3 random_color() {
    return hsv_to_rgb(floorf(random_float() * 360.0f), 0.75f, 0.45f);
}
