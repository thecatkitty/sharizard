#include <cstring>

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
    gfx_get_glyph_dimensions(&glyph);

    int  x = position_.x * glyph.x + (glyph.x / 2);
    int  y = position_.y * glyph.y + (glyph.y * 3 / 4);
    auto size = shiz_vec2i{(size_.x - 2) * glyph.x, glyph.y * 3 / 2};

    char buff[GFX_COLUMNS / 2];
    shiz_canvas_load_string(&field_, buff, sizeof(buff));

    auto inner_size = shiz_vec2i{size.x + 2, size.y};
    gfx_fill_rectangle(x, y, &size, GFX_COLOR_WHITE);
    gfx_draw_rectangle(x, y, &size, GFX_COLOR_BLACK);
    gfx_draw_rectangle(x - 1, y, &inner_size, GFX_COLOR_BLACK);

    auto pos = get_absolute_position();
    gfx_draw_text(buff, pos.x + (8 - strlen(buff)) / 2 + 1, pos.y + 1);
}

int
button::click(int x, int y)
{
    return field_.data;
}
