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
    gfx_dimensions glyph;
    gfx_get_glyph_dimensions(&glyph);
    auto rect = get_position();
    rect.left *= glyph.width;
    rect.width *= glyph.width;
    rect.top *= glyph.height;
    rect.height *= glyph.height;
    gfx_fill_rectangle(&rect, GFX_COLOR_WHITE);

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

    rect_.width = GFX_COLUMNS - 2;
    rect_.height = shiz_canvas_print(rect_.top, buffer) + 1;
}
