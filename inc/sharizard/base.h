#ifndef SHARIZARD_BASE_H
#define SHARIZARD_BASE_H

#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
#define SHIZ_EXTERNC_BEGIN                                                     \
    extern "C"                                                                 \
    {
#define SHIZ_EXTERNC_END }
#else
#define SHIZ_EXTERNC_BEGIN
#define SHIZ_EXTERNC_END
#endif

typedef enum
{
    SHIZ_COLOR_BLACK = 0,
    SHIZ_COLOR_NAVY = 1,
    SHIZ_COLOR_GREEN = 2,
    SHIZ_COLOR_TEAL = 3,
    SHIZ_COLOR_MAROON = 4,
    SHIZ_COLOR_PURPLE = 5,
    SHIZ_COLOR_OLIVE = 6,
    SHIZ_COLOR_SILVER = 7,
    SHIZ_COLOR_GRAY = 8,
    SHIZ_COLOR_BLUE = 9,
    SHIZ_COLOR_LIME = 10,
    SHIZ_COLOR_CYAN = 11,
    SHIZ_COLOR_RED = 12,
    SHIZ_COLOR_FUCHSIA = 13,
    SHIZ_COLOR_YELLOW = 14,
    SHIZ_COLOR_WHITE = 15,
    SHIZ_COLOR_UNKNOWN = -1
} shiz_color;

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
