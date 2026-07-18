#ifndef DEPS_LAVENDER_H
#define DEPS_LAVENDER_H

#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>

typedef struct
{
    int16_t  width;
    int16_t  height;
    uint16_t opl;
    uint8_t  bpp;
    void    *bits;
    off_t    offset;
    int16_t  chunk_top;
    int16_t  chunk_height;
} gfx_bitmap;

extern void
pal_disable_mouse(void);

extern const char *
pal_get_version_string(void);

#endif // DEPS_LAVENDER_H
