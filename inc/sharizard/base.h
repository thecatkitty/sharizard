#ifndef SHARIZARD_BASE_H
#define SHARIZARD_BASE_H

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

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

#endif // SHARIZARD_BASE_H
