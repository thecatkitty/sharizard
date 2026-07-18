#ifndef CANVAS_CANVAS_H
#define CANVAS_CANVAS_H

#include "deps-lavender.h"
#include <sharizard.h>

#define TEXT_WIDTH (GFX_COLUMNS - 2)

void
shiz_canvas_load_string(shiz_field *field, char *buff, size_t length);

int
shiz_canvas_print(int top, char *text);

void
shiz_canvas_init_frame(void);

void
shiz_canvas_enter_page(shiz_page *pages, int id);

int
shiz_canvas_click(uint16_t x, uint16_t y);

int
shiz_canvas_key(uint16_t scancode);

bool
shiz_canvas_animate(bool valid);

void
shiz_canvas_set_error(char *message);

#endif // CANVAS_CANVAS_H
