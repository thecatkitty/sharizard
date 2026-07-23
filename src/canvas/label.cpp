#include <cstring>

#include "widgets.hpp"

using namespace shiz::canvas;

int
label::click(int x, int y)
{
    if (0 == (SHIZFF_FOOTER & field_.flags))
    {
        return 0;
    }

    auto &page = *get_page();
    page.proc(SHIZM_NOTIFY,
              reinterpret_cast<void *>(0x100 + (&field_ - page.fields)),
              page.data);
    return 0;
}

void
label::draw()
{
    shiz_vec2i glyph;
    gfx_get_glyph_dimensions(&glyph);

    auto pos = get_absolute_position();
    auto size = shiz_vec2i{size_.x * glyph.x, size_.y * glyph.y};
    gfx_fill_rectangle(pos.x * glyph.x, pos.y * glyph.y, &size,
                       GFX_COLOR_WHITE);

    char buffer[GFX_COLUMNS * 4];
    if (SHIZFF_DYNAMIC & field_.flags)
    {
        std::strncpy(buffer, reinterpret_cast<const char *>(field_.data),
                     sizeof(buffer));
    }
    else
    {
        pal_load_string(field_.data, buffer, sizeof(buffer));
    }

    if (SHIZFF_FOOTER & field_.flags)
    {
        auto src = buffer;
        auto dst = buffer;
        bool skipping = false;

        while (*src)
        {
            if ('<' == *src)
            {
                skipping = true;
            }

            if (!skipping)
            {
                *dst = *src;
                dst++;
            }

            if ('>' == *src)
            {
                skipping = false;
            }

            src++;
        }
        *dst = 0;
    }

    size_.x = GFX_COLUMNS - 2;
    size_.y = shiz_canvas_print(position_.y, buffer) + 1;
}
