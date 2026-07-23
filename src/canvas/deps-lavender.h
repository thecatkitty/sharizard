#ifndef CANVAS_DEPS_LAVENDER_H
#define CANVAS_DEPS_LAVENDER_H

#include <sharizard/base.h>

#include "../deps-lavender.h"

#define CONFIG_SHIZ_CHECKBOX_MARK_CHARACTER "x"
#define CONFIG_SHIZ_RADIO_FIELD_CHARACTER   "○"
#if defined(HAVE_GFX_CHARSET)
#define CONFIG_SHIZ_RADIO_MARK_CHARACTER "•"
#else
#define CONFIG_SHIZ_RADIO_MARK_CHARACTER "x"
#endif

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

extern uint16_t
pal_get_keystroke(void);

extern void
pal_enable_mouse(void);

extern uint16_t
pal_get_mouse(uint16_t *x, uint16_t *y);

extern int
pal_load_string(unsigned id, char *buffer, int max_length);

extern uint32_t
palpp_get_counter(void);

extern uint32_t
palpp_get_ticks(unsigned ms);

#endif // CANVAS_DEPS_LAVENDER_H
