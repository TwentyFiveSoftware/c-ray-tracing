#pragma once

#include <stdint.h>

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb;

void save_image_as_png(const char *path, rgb *pixels);
