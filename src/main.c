#include "image.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    rgb *pixels = calloc(WIDTH * HEIGHT, sizeof(rgb));
    if (!pixels) {
        return 1;
    }

    for (uint32_t y = 0; y < HEIGHT; ++y) {
        for (uint32_t x = 0; x < WIDTH; ++x) {
            float u = ((float) x) / ((float) (WIDTH - 1));
            float v = ((float) y) / ((float) (HEIGHT - 1));

            size_t index = (y * WIDTH + x);
            (pixels + index)->r = (uint8_t) (u * 0xFF);
            (pixels + index)->g = (uint8_t) (v * 0xFF);
            (pixels + index)->b = (uint8_t) (0.25 * 0xFF);
        }
    }

    save_image_as_png("render.png", pixels);

    free(pixels);
    return 0;
}
