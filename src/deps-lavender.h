#ifndef DEPS_LAVENDER_H
#define DEPS_LAVENDER_H

#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>

#define CONFIG_ENCUI_CHECKBOX_MARK_CHARACTER "x"
#define CONFIG_ENCUI_RADIO_FIELD_CHARACTER   "○"
#if defined(HAVE_GFX_CHARSET)
#define CONFIG_ENCUI_RADIO_MARK_CHARACTER "•"
#else
#define CONFIG_ENCUI_RADIO_MARK_CHARACTER "x"
#endif

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

typedef struct
{
    int width;
    int height;
} gfx_dimensions;

typedef struct
{
    int left;
    int top;
    int width;
    int height;
} gfx_rect;

typedef enum
{
    GFX_COLOR_BLACK = 0,
    GFX_COLOR_NAVY = 1,
    GFX_COLOR_GREEN = 2,
    GFX_COLOR_TEAL = 3,
    GFX_COLOR_MAROON = 4,
    GFX_COLOR_PURPLE = 5,
    GFX_COLOR_OLIVE = 6,
    GFX_COLOR_SILVER = 7,
    GFX_COLOR_GRAY = 8,
    GFX_COLOR_BLUE = 9,
    GFX_COLOR_LIME = 10,
    GFX_COLOR_CYAN = 11,
    GFX_COLOR_RED = 12,
    GFX_COLOR_FUCHSIA = 13,
    GFX_COLOR_YELLOW = 14,
    GFX_COLOR_WHITE = 15,
    GFX_COLOR_UNKNOWN = -1
} gfx_color;

#define GFX_COLUMNS 80
#define GFX_LINES   25

#define PAL_MOUSE_LBUTTON 0x0001

#ifndef VK_BACK
// Virtual key code definitions borrowed from Windows API
// Codes for 0-9 and A-Z are the same as ASCII
#define VK_BACK      0x08
#define VK_TAB       0x09
#define VK_RETURN    0x0D
#define VK_ESCAPE    0x1B
#define VK_PRIOR     0x21
#define VK_NEXT      0x22
#define VK_END       0x23
#define VK_HOME      0x24
#define VK_LEFT      0x25
#define VK_UP        0x26
#define VK_RIGHT     0x27
#define VK_DOWN      0x28
#define VK_INSERT    0x2D
#define VK_DELETE    0x2E
#define VK_F1        0x70
#define VK_F2        0x71
#define VK_F3        0x72
#define VK_F4        0x73
#define VK_F5        0x74
#define VK_F6        0x75
#define VK_F7        0x76
#define VK_F8        0x77
#define VK_F9        0x78
#define VK_F10       0x79
#define VK_F11       0x7A
#define VK_F12       0x7B
#define VK_OEM_PLUS  0xBB
#define VK_OEM_MINUS 0xBD
#endif

// Get width and height of a glyph in pixels
extern void
gfx_get_glyph_dimensions(gfx_dimensions *dim);

// Get width and height of the screen area in pixels
extern void
gfx_get_screen_dimensions(gfx_dimensions *dim);

extern bool
gfx_draw_bitmap(gfx_bitmap *bm, int x, int y);

extern bool
gfx_draw_line(const gfx_rect *rect, gfx_color color);

extern bool
gfx_draw_rectangle(const gfx_rect *rect, gfx_color color);

extern bool
gfx_fill_rectangle(const gfx_rect *rect, gfx_color color);

extern bool
gfx_draw_text(const char *str, uint16_t x, uint16_t y);

extern uint16_t
pal_get_keystroke(void);

extern void
pal_disable_mouse(void);

extern void
pal_enable_mouse(void);

extern uint16_t
pal_get_mouse(uint16_t *x, uint16_t *y);

extern int
pal_load_string(unsigned id, char *buffer, int max_length);

extern const char *
pal_get_version_string(void);

extern uint32_t
palpp_get_counter(void);

extern uint32_t
palpp_get_ticks(unsigned ms);

// Get code point from UTF-8 sequence
// Returns the code point (0 on NUL or error)
// *length will contain the length of the sequence (0 on error)
extern uint16_t
utf8_get_codepoint(const char *sequence, int *length);

#endif // DEPS_LAVENDER_H
