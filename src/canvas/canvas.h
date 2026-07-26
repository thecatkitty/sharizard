#ifndef CANVAS_CANVAS_H
#define CANVAS_CANVAS_H

#include <sharizard.h>

#define SHIZ_CANVAS_COLUMNS 80 //!< Text grid width.
#define SHIZ_CANVAS_ROWS    25 //!< Text grid height.

#define SHIZ_CANVAS_CHECKBOX_MARK_CHARACTER "x"
#define SHIZ_CANVAS_RADIO_FIELD_CHARACTER   "○"
#if defined(__ia16__)
#define SHIZ_CANVAS_RADIO_MARK_CHARACTER "•" // IBM Graphics 0x07
#else
#define SHIZ_CANVAS_RADIO_MARK_CHARACTER "x"
#endif

#define TEXT_WIDTH (SHIZ_CANVAS_COLUMNS - 2)

void
shiz_canvas_load_string(shiz_field *field, char *buff, size_t length);

int
shiz_canvas_print(int top, char *text);

void
shiz_canvas_init_frame(const shiz_wizard *wizard);

void
shiz_canvas_enter_page(shiz_page *pages, int id);

int
shiz_canvas_click(int x, int y);

int
shiz_canvas_key(uint16_t scancode);

bool
shiz_canvas_animate(bool valid);

void
shiz_canvas_set_error(char *message);

#endif // CANVAS_CANVAS_H
