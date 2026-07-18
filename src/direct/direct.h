#ifndef _UI_DIRECT_H_
#define _UI_DIRECT_H_

#include "../deps-lavender.h"
#include <sharizard.h>

#define TEXT_WIDTH (GFX_COLUMNS - 2)

void
shiz_direct_load_string(shiz_field *field, char *buff, size_t length);

int
shiz_direct_print(int top, char *text);

void
shiz_direct_init_frame(void);

void
shiz_direct_enter_page(shiz_page *pages, int id);

int
shiz_direct_click(uint16_t x, uint16_t y);

int
shiz_direct_key(uint16_t scancode);

bool
shiz_direct_animate(bool valid);

void
shiz_direct_set_error(char *message);

#endif
