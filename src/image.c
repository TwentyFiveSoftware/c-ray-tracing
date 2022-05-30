#include "image.h"
#include "constants.h"
#include <png.h>

void save_image_as_png(const char *path, rgb *pixels) {
    FILE *file = fopen(path, "wb");
    if (!file) {
        return;
    }

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        fclose(file);
        return;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        fclose(file);
        return;
    }

    png_set_IHDR(png_ptr,
                 info_ptr,
                 WIDTH,
                 HEIGHT,
                 8,
                 PNG_COLOR_TYPE_RGB,
                 PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT,
                 PNG_FILTER_TYPE_DEFAULT);

    png_byte **rows = png_malloc(png_ptr, HEIGHT * sizeof(png_byte *));

    for (uint32_t y = 0; y < HEIGHT; ++y) {
        png_byte *row = png_malloc(png_ptr, WIDTH * sizeof(uint8_t) * 3);
        rows[y] = row;

        for (uint32_t x = 0; x < WIDTH; ++x) {
            rgb *pixel = pixels + y * WIDTH + x;
            row[x * 3 + 0] = pixel->r;
            row[x * 3 + 1] = pixel->g;
            row[x * 3 + 2] = pixel->b;
        }
    }

    png_init_io(png_ptr, file);
    png_set_rows(png_ptr, info_ptr, rows);
    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    for (uint32_t y = 0; y < HEIGHT; ++y) {
        png_free(png_ptr, rows[y]);
    }
    png_free(png_ptr, rows);

    fclose(file);
}
