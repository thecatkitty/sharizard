#ifndef SHARIZARD_BASE_H
#define SHARIZARD_BASE_H

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

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
