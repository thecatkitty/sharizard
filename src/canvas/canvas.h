#ifndef CANVAS_CANVAS_H
#define CANVAS_CANVAS_H

#include "deps-lavender.h"
#include <sharizard.h>

#define SHIZ_CANVAS_COLUMNS 80 //!< Text grid width.
#define SHIZ_CANVAS_ROWS    25 //!< Text grid height.

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
