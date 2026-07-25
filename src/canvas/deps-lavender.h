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

extern void
pal_enable_mouse(void);

extern int
pal_load_string(unsigned id, char *buffer, int max_length);

#endif // CANVAS_DEPS_LAVENDER_H
