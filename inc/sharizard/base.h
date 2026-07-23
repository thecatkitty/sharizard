#ifndef SHARIZARD_BASE_H
#define SHARIZARD_BASE_H

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum
{
    SHIZ_PXFORMAT_MONO1,
    SHIZ_PXFORMAT_IRGB1111,
    SHIZ_PXFORMAT_ARGB8888,
} shiz_pxformat;

typedef struct
{
    int x;
    int y;
} shiz_vec2i;

typedef struct
{
    shiz_vec2i     size;
    shiz_pxformat  format;
    size_t         stride;
    const uint8_t *pixels;
} shiz_bitmap;

#endif // SHARIZARD_BASE_H
