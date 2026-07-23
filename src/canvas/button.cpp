#include <cstring>

#include <sharizard/drawing.h>

#include "widgets.hpp"

using namespace shiz::canvas;

button::button(shiz_field &field) : widget{field}
{
    size_.x = 11;
    size_.y = 3;
}

void
button::draw()
{
    shiz_vec2i glyph;
    shizd_get_cell_size(nullptr, &glyph);

    int  x = position_.x * glyph.x + (glyph.x / 2);
    int  y = position_.y * glyph.y + (glyph.y * 3 / 4);
    auto size = shiz_vec2i{(size_.x - 2) * glyph.x, glyph.y * 3 / 2};

    char buff[GFX_COLUMNS / 2];
    shiz_canvas_load_string(&field_, buff, sizeof(buff));

    auto inner_size = shiz_vec2i{size.x + 2, size.y};
    shizd_fill_rectangle(nullptr, x, y, &size, SHIZ_COLOR_WHITE);
    shizd_draw_rectangle(nullptr, x, y, &size, SHIZ_COLOR_BLACK);
    shizd_draw_rectangle(nullptr, x - 1, y, &inner_size, SHIZ_COLOR_BLACK);

    auto pos = get_absolute_position();
    shizd_draw_text(nullptr, pos.x + (8 - strlen(buff)) / 2 + 1, pos.y + 1,
                    buff);
}

int
button::click(int x, int y)
{
    return field_.data;
}
