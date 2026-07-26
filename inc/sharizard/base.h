#ifndef SHARIZARD_BASE_H
#define SHARIZARD_BASE_H

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
#define SHIZ_EXTERNC_BEGIN                                                     \
    extern "C"                                                                 \
    {
#define SHIZ_EXTERNC_END }
#else
#define SHIZ_EXTERNC_BEGIN
#define SHIZ_EXTERNC_END
#endif

/**
 * Standard 4-bit RGBI colors.
 *
 * Values correspond to the IBM Enhanced Color Display (5154) RGBI encoding.
 */
typedef enum
{
    SHIZ_COLOR_BLACK = 0,    //!< 0000 Black.
    SHIZ_COLOR_NAVY = 1,     //!< 0001 Blue.
    SHIZ_COLOR_GREEN = 2,    //!< 0010 Green.
    SHIZ_COLOR_TEAL = 3,     //!< 0011 Cyan.
    SHIZ_COLOR_MAROON = 4,   //!< 0100 Red.
    SHIZ_COLOR_PURPLE = 5,   //!< 0101 Magenta.
    SHIZ_COLOR_OLIVE = 6,    //!< 0110 Brown (or Dark Yellow).
    SHIZ_COLOR_SILVER = 7,   //!< 0111 Gray 1.
    SHIZ_COLOR_GRAY = 8,     //!< 1000 Gray 2.
    SHIZ_COLOR_BLUE = 9,     //!< 1001 Light Blue.
    SHIZ_COLOR_LIME = 10,    //!< 1010 Light Green.
    SHIZ_COLOR_CYAN = 11,    //!< 1011 Light Cyan.
    SHIZ_COLOR_RED = 12,     //!< 1100 Light Red.
    SHIZ_COLOR_FUCHSIA = 13, //!< 1101 Light Magenta.
    SHIZ_COLOR_YELLOW = 14,  //!< 1110 Light Yellow.
    SHIZ_COLOR_WHITE = 15,   //!< 1111 White.
    SHIZ_COLOR_UNKNOWN = -1  //!< Unknown color.
} shiz_color;

/**
 * Pixel format of a bitmap.
 */
typedef enum
{
    SHIZ_PXFORMAT_MONO1,    //!< Monochrome (1 bit per pixel).
    SHIZ_PXFORMAT_IRGB1111, //!< 4-bit IRGB color encoding.
    SHIZ_PXFORMAT_RGB888,   //!< 24-bit RGB (8 bits per component).
} shiz_pxformat;

/**
 * Two-dimensional integer vector.
 *
 * Used for positions, dimensions, and other planar coordinates.
 */
typedef struct
{
    int x; //!< Horizontal component.
    int y; //!< Vertical component.
} shiz_vec2i;

/**
 * Immutable bitmap image.
 */
typedef struct
{
    shiz_vec2i     size;   //!< Width and height in pixels.
    shiz_pxformat  format; //!< Pixel format.
    size_t         stride; //!< Number of bytes between adjacent scanlines.
    const uint8_t *pixels; //!< Pointer to the first pixel.
} shiz_bitmap;

#endif // SHARIZARD_BASE_H
