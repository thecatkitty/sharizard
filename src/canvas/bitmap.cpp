#include <sharizard/drawing.h>

#include "widgets.hpp"

using namespace shiz::canvas;

bitmap::bitmap(shiz_field &field) : widget{field}
{
    shiz_vec2i glyph;
    shizd_get_cell_size(nullptr, &glyph);

    auto &bm = *reinterpret_cast<shiz_bitmap *>(field_.data);
    size_.x = (bm.size.x + glyph.x - 1) / glyph.x;
    size_.y = (bm.size.y + glyph.y - 1) / glyph.y + 1;
}

void
bitmap::draw()
{
    shiz_vec2i glyph;
    shizd_get_cell_size(nullptr, &glyph);

    auto &bm = *reinterpret_cast<shiz_bitmap *>(field_.data);
    auto  pos = get_absolute_position();

    auto x = pos.x;
    if (SHIZFF_CENTER == (SHIZFF_ALIGN & field_.flags))
    {
        x += (TEXT_WIDTH - size_.x) / 2;
    }
    else if (SHIZFF_RIGHT == (SHIZFF_ALIGN & field_.flags))
    {
        x += TEXT_WIDTH - size_.x;
    }
    x *= glyph.x;

    auto y = pos.y * glyph.y;

    shizd_draw_bitmap(nullptr, x, y, &bm);
}
