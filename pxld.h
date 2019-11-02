
#ifndef PXLD_H
#define PXLD_H 1

#include <stdint.h>
#include <stdlib.h>
#include "scl/scl.h"

typedef uint8_t byte;
typedef int64_t unit_t;
#define UNIT_MAX INT64_MAX

#if UNIT_MAX == 0x7F
#define UNIT_WIDTH 1
#elif UNIT_MAX == 0x7FFF
#define UNIT_WIDTH 2
#elif UNIT_MAX == 0x7FFFFFFF
#define UNIT_WIDTH 4
#elif UNIT_MAX == 0x7FFFFFFFFFFFFFFF
#define UNIT_WIDTH 8
#else
#error unknown UNIT_MAX
#endif

#if INT64_MAX > SIZE_MAX
    #error INT64_MAX is greater than SIZE_MAX
#endif

typedef enum { L, LA, RGB, RGBA } mode_t;

typedef struct
{
    unit_t x;
    unit_t y;
} point_t;

static inline
double point_dist(point_t a, point_t b)
{
    return sqrt(pow(a.x - b.x, 2.0) + pow(a.y - b.y, 2.0));
}

static inline
double point_inv_dist(point_t a, point_t b, double max)
{
    return max - fmin(point_dist(a, b), max);
}

static inline
double point_angle(point_t a, point_t b)
{
    return atan((double)(b.x - a.x) / (double)(b.y - a.y));
}

static inline
point_t point_random(point_t min, point_t max)
{
    return (point_t)
        {random_range(min.x, max.x),
        random_range(min.y, max.y)};
}

typedef struct
{
    mode_t mode;
    byte *buffer;
} color_t;

static inline
unit_t get_color_width(mode_t mode)
{
    switch (mode)
    {
    case L:     return 1;
    case LA:    return 2;
    case RGB:   return 3;
    case RGBA:  return 4;

    default:
        error = ERROR_BAD_ARGUMENTS;
        return 0;
    }
}

static inline
uint8_t get_color_code(mode_t mode)
{
    switch (mode)
    {
    //  RGB or L: 0x01, alpha channel: 0x02
    case L:     return 0x00;
    case LA:    return 0x02;
    case RGB:   return 0x01;
    case RGBA:  return 0x03;

    default:
        error = ERROR_BAD_ARGUMENTS;
        return 0;
    }
}

typedef struct image
{
    mode_t mode;
    byte *buffer;

    point_t size;
    unit_t color_width;
    unit_t x_width;
    unit_t y_width;
} image_t;

static inline
void initialize_image(image_t *image, mode_t mode, point_t size)
{
    unit_t x_width;
    unit_t y_width;
    unit_t color_width;

    color_width = get_color_width(mode);
    if (error) return;

    x_width = mul(unit_t, size.x, color_width);
    if (error) return;

    y_width = mul(unit_t, size.y, x_width);
    if (error) return;

    image->buffer = malloc(y_width);
    if (image->buffer == NULL)
    {
        error = ERROR_NO_MEMORY;
        return;
    }
    image->mode = mode;

    image->size = size;
    image->color_width = color_width;
    image->x_width = x_width;
    image->y_width = y_width;
}

static inline
void destroy_image(image_t *image)
{
    free(image->buffer);
}

static inline
byte *image_get_pixel(image_t *image, point_t coor)
{
    return image->buffer +
        (coor.y * image->x_width) + (coor.x * image->color_width);
}

static inline
void image_draw(image_t *image, byte *color)
{
    for (unit_t i = 0; i < image->y_width; i += image->color_width)
    {
        for (unit_t c = 0; c < image->color_width; c += 1)
        {
            image->buffer[i + c] = color[c];
        }
    }
}

static inline
void image_draw_dot(image_t *image, point_t coor, byte *color)
{
    for (unit_t c = 0; c < image->color_width; c += 1)
    {
        image->buffer[
        (coor.y * image->x_width) + (coor.x * image->color_width) + c] \
        = color[c];
    }
}

static inline
void image_draw_rectangle(image_t *image, point_t coor1, point_t coor2,
    byte *color)
{
    for (unit_t y = coor1.y * image->x_width, yEnd = coor2.y * image->x_width;
        y <= yEnd; y += image->x_width)
    {
        for (unit_t x = coor1.x * image->color_width,
            xEnd = coor2.x * image->color_width;
            x <= xEnd; x += 1)
        {
            for (unit_t c = 0; c < image->color_width; c += 1)
            {
                image->buffer[y + x + c] = color[c];
            }
        }
    }
}

static inline
void image_map(image_t *image, void (*map) (point_t coor, byte *color))
{
    for (unit_t y = 0, yIndex = 0; y < image->y_width;
        y += image->x_width, yIndex += 1)
    {
        for (unit_t x = 0, xIndex = 0; x < image->x_width;
            x += image->color_width, xIndex += 1)
        {
            map((point_t) {xIndex, yIndex}, image->buffer + y + x);
        }
    }
}

static inline
size_t image_save(image_t *image, FILE *file)
{
    size_t byte_number;
    uint8_t unit_width = UNIT_WIDTH;

    byte_number = 0;

    byte_number += safe_fwrite("img.", 4, file);
    if (error) return byte_number;

    byte_number += safe_fwrite(&(unit_width), 1, file);
    if (error) return byte_number;

    byte_number += safe_fwrite(&(image->color_width), sizeof(unit_t), file);
    if (error) return byte_number;

    byte_number += safe_fwrite(&(image->size.x), sizeof(unit_t), file);
    if (error) return byte_number;

    byte_number += safe_fwrite(&(image->size.y), sizeof(unit_t), file);
    if (error) return byte_number;

    byte_number += safe_fwrite(image->buffer, image->y_width, file);
    if (error) return byte_number;

    return byte_number;
}

static inline
size_t image_save_name(image_t *image, const char *name)
{
    FILE *file;
    size_t byte_number;

    file = fopen(name, "wb");
    if (file == NULL)
    {
        error = ERROR_FOPEN;
        return 0;
    }

    byte_number = image_save(image, file);
    fclose(file);

    return byte_number;
}

typedef struct animation
{
    image_t image;
    void (*start) (struct animation *self);
    bool (*step) (struct animation *self);
} animation_t;

static inline
void initialize_animation(animation_t *animation, mode_t mode, point_t size)
{
    initialize_image(&(animation->image), mode, size);
}

static inline
size_t animation_render(animation_t *animation, FILE *file)
{
    size_t byte_number;
    uint8_t unit_width = UNIT_WIDTH;

    byte_number = 0;

    byte_number += safe_fwrite("ani.", 4, file);
    if (error) return byte_number;

    byte_number += safe_fwrite(&(unit_width), 1, file);
    if (error) return byte_number;

    byte_number +=
        safe_fwrite(&(animation->image.color_width), sizeof(unit_t), file);
    if (error) return byte_number;

    byte_number +=
        safe_fwrite(&(animation->image.size.x), sizeof(unit_t), file);
    if (error) return byte_number;

    byte_number +=
        safe_fwrite(&(animation->image.size.y), sizeof(unit_t), file);
    if (error) return byte_number;

    animation->start(animation);

    byte_number +=
        safe_fwrite(animation->image.buffer, animation->image.y_width, file);
    if (error) return byte_number;

    while (animation->step(animation))
    {
        byte_number +=
            safe_fwrite(animation->image.buffer, animation->image.y_width,
            file);
        if (error) return byte_number;
    }

    return byte_number;
}

static inline
size_t animation_render_name(animation_t *animation, const char *name)
{
    FILE *file;
    size_t byte_number;

    file = fopen(name, "wb");
    if (file == NULL)
    {
        error = ERROR_FOPEN;
        return 0;
    }

    byte_number = animation_render(animation, file);
    fclose(file);

    return byte_number;
}

#endif /* PXLD_H */
