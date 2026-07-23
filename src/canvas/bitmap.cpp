#include "widgets.hpp"

using namespace shiz::canvas;

bitmap::bitmap(shiz_field &field) : widget{field}
{
    shiz_vec2i glyph;
    gfx_get_glyph_dimensions(&glyph);

    auto &bm = *reinterpret_cast<gfx_bitmap *>(field_.data);
    size_.x = (bm.width + glyph.x - 1) / glyph.x;
    size_.y = (bm.height + glyph.y - 1) / glyph.y + 1;
}

void
bitmap::draw()
{
    shiz_vec2i glyph;
    gfx_get_glyph_dimensions(&glyph);

    auto &bm = *reinterpret_cast<gfx_bitmap *>(field_.data);
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

    gfx_draw_bitmap(&bm, x, y);
}
