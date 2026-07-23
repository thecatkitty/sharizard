#include <algorithm>
#include <cstdio>
#include <cstring>

#include "widgets.hpp"

using namespace shiz::canvas;

option::option(shiz_field &field) : widget{field}
{
    size_.x = TEXT_WIDTH;
    size_.y = 2;
}

void
option::draw()
{
    char buffer[GFX_COLUMNS * 4] = "   ";
    shiz_canvas_load_string(&field_, buffer + 3, sizeof(buffer) - 8);

    auto page = get_page();
    if (nullptr != page)
    {
        auto pos =
            std::count_if(page->fields, &field_, [](const shiz_field &field) {
                return SHIZFT_OPTION == field.type;
            });

        if (7 > pos)
        {
            std::sprintf(buffer + strlen(buffer), " [F%d]", int(pos + 1));
        }
    }

    shiz_canvas_print(position_.y, buffer);

    mark(SHIZFF_CHECKED & field_.flags);
}

int
option::click(int x, int y)
{
    if (nullptr == parent_)
    {
        return 0;
    }

    for (auto &widget : *reinterpret_cast<panel *>(parent_))
    {
        if (SHIZFT_OPTION != widget->get_model().type)
        {
            continue;
        }

        auto &that = *reinterpret_cast<option *>(widget.get());
        that.set(false);
    }

    set(true);
    return 0;
}

void
option::mark(bool checked)
{
    shiz_vec2i glyph;
    gfx_get_glyph_dimensions(&glyph);

    auto pos = get_absolute_position();
    gfx_fill_rectangle((pos.x + 1) * glyph.x, pos.y * glyph.y, &glyph,
                       GFX_COLOR_WHITE);

    char buff[4];
    strcpy(buff, CONFIG_SHIZ_RADIO_FIELD_CHARACTER);
    gfx_draw_text(buff, pos.x + 1, pos.y);
    if (checked)
    {
        strcpy(buff, CONFIG_SHIZ_RADIO_MARK_CHARACTER);
        gfx_draw_text(buff, pos.x + 1, pos.y);
    }
}

void
option::set(bool checked)
{
    mark(checked);
    if (checked)
    {
        field_.flags |= SHIZFF_CHECKED;
    }
    else
    {
        field_.flags &= ~SHIZFF_CHECKED;
    }
}
