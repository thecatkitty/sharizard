#include <cstring>

#include "widgets.hpp"

using namespace shiz::canvas;

checkbox::checkbox(shiz_field &field)
    : widget{field}, box_position_{}, box_size_{}
{
    shiz_vec2i glyph;
    gfx_get_glyph_dimensions(&glyph);

    size_.x = TEXT_WIDTH;
    size_.y = 2;

    box_position_.x = glyph.x * 2 / 3 + 1;
    box_position_.y = (glyph.y - glyph.x) / 2;
    box_size_.x = box_size_.y = glyph.x + 4;
}

void
checkbox::draw()
{
    char buffer[GFX_COLUMNS * 4] = "   ";
    shiz_canvas_load_string(&field_, buffer + 3, sizeof(buffer) - 8);
    std::strcat(buffer, " [F8]");
    shiz_canvas_print(position_.y, buffer);

    mark(SHIZFF_CHECKED & field_.flags);
}

int
checkbox::click(int x, int y)
{
    field_.flags ^= SHIZFF_CHECKED;

#if defined(CONFIG_HAVE_GFX_XOR_BLENDING)
    mark(true);
#else
    mark(SHIZFF_CHECKED & field_.flags);
#endif

    return 0;
}

void
checkbox::mark(bool checked)
{
    shiz_vec2i glyph;
    gfx_get_glyph_dimensions(&glyph);

    auto pos = get_absolute_position();
    int  x = pos.x * glyph.x + box_position_.x;
    int  y = pos.y * glyph.y + box_position_.y;

    gfx_draw_rectangle(x, y, &box_size_, GFX_COLOR_BLACK);
#if !defined(CONFIG_HAVE_GFX_XOR_BLENDING)
    gfx_fill_rectangle(x, y, &box_size_, GFX_COLOR_WHITE);
#endif

    if (checked)
    {
        gfx_draw_text(CONFIG_SHIZ_CHECKBOX_MARK_CHARACTER, pos.x + 1, pos.y);
    }
}
