#include <algorithm>
#include <cstring>
#include <iterator>
#include <memory>
#include <vector>

extern "C"
{
#include "../resource.h"
#include "direct.h"
}

#include "widgets.hpp"

// Screen metrics
static gfx_dimensions _glyph = {0, 0};
static gfx_rect       _screen = {0, 0, 0, 0};

// Buttons
static shiz_field   _cancel_field{0, SHIZFF_STATIC, IDS_CANCEL};
static shiz_field   _back_field{0, SHIZFF_STATIC, IDS_BACK};
static shiz_field   _next_field{0, SHIZFF_STATIC, IDS_NEXT};
static shiz::button _cancel{_cancel_field};
static shiz::button _back{_back_field};
static shiz::button _next{_next_field};
static bool         _mouse_down;

// Page state
static shiz_page *_page;

std::unique_ptr<shiz::panel> panel_{};

void
shiz_direct_init_frame(void)
{
    gfx_dimensions dim;
    gfx_get_screen_dimensions(&dim);
    gfx_get_glyph_dimensions(&_glyph);

    _screen.width = dim.width;
    _screen.height = dim.height;

    gfx_rect bar = {0, 0, _screen.width, 3 * _glyph.height + 1};
    bar.top = _screen.height - bar.height;
    gfx_fill_rectangle(&bar, GFX_COLOR_BLACK);

    gfx_draw_text(pal_get_version_string(), 1, 22);
    gfx_draw_text("https://celones.pl/lavender", 1, 23);
    gfx_draw_text("(C) 2021-2026 Mateusz Karcz", 1, 24);

    _next.move(GFX_COLUMNS - 22, GFX_LINES - 3);
    _cancel.move(GFX_COLUMNS - 11, GFX_LINES - 3);
}

static void
_draw_title(char *title)
{
    gfx_rect bar = {0, 0, _screen.width, _glyph.height + 1};
    gfx_fill_rectangle(&bar, GFX_COLOR_BLACK);

#if defined(CONFIG_HAVE_GFX_CHARSET)
    utf8_encode(title, title, pal_wctob);
#endif
    gfx_draw_text(title, 1, 0);
}

static void
_draw_background(void)
{
    gfx_rect bg = {0, _glyph.height, _screen.width,
                   (GFX_LINES - 4) * _glyph.height};
    gfx_fill_rectangle(&bg, GFX_COLOR_WHITE);

    gfx_rect footer = {0, 0, _screen.width / 2, 3 * _glyph.height};
    footer.left = footer.width;
    footer.top = _screen.height - footer.height;
    gfx_fill_rectangle(&footer, GFX_COLOR_BLACK);
}

static bool
_is_pressed(const shiz::widget &widget, uint16_t msx, uint16_t msy)
{
    gfx_rect pos = widget.get_position();
    if (0 > pos.left)
    {
        return false;
    }

    if ((pos.left > int(msx)) || ((pos.left + pos.width) <= int(msx)))
    {
        return false;
    }

    if ((pos.top > int(msy)) || ((pos.top + pos.height) <= int(msy)))
    {
        return false;
    }

    return true;
}

static void
_create_controls(shiz_page *page)
{
    panel_ = std::make_unique<shiz::panel>(*page);

    uint16_t x, y;
    _mouse_down = PAL_MOUSE_LBUTTON & pal_get_mouse(&x, &y);

    int  cy = 2;
    bool has_checkbox = false;

    for (int i = 0; i < page->length; i++)
    {
        shiz_field *field = &page->fields[i];

        if (SHIZFT_SEPARATOR == field->type)
        {
            cy += field->data;
        }

        if (SHIZFT_LABEL == field->type)
        {
            auto &label = panel_->create<shiz::label>(*field);
            if (SHIZFF_FOOTER & field->flags)
            {
                label.move(1, GFX_LINES - 5);
                label.draw();
            }
            else
            {
                label.move(1, cy);
                label.draw();
                cy = shiz::get_bottom(label.get_area());
            }
        }

        if (SHIZFT_TEXTBOX == field->type)
        {
            auto &textbox = panel_->create<shiz::textbox>(*field);
            textbox.move(1, cy);
            textbox.draw();
            cy = shiz::get_bottom(textbox.get_area());
        }

        if (!has_checkbox && (SHIZFT_CHECKBOX == field->type))
        {
            has_checkbox = true;

            auto &checkbox = panel_->create<shiz::checkbox>(*field);
            checkbox.move(1, GFX_LINES - 5);
            checkbox.draw();
        }

        if (SHIZFT_OPTION == field->type)
        {
            auto &option = panel_->create<shiz::option>(*field);
            option.move(1, cy);
            option.draw();
            cy = shiz::get_bottom(option.get_area());
        }

        if (SHIZFT_BITMAP == field->type)
        {
            auto &bitmap = panel_->create<shiz::bitmap>(*field);
            bitmap.move(1, cy);
            bitmap.draw();
            cy = shiz::get_bottom(bitmap.get_area());
        }
    }
}

void
shiz_direct_enter_page(shiz_page *pages, int id)
{
    _page = pages + id;
    _page->proc(SHIZM_INIT, NULL, _page->data);

    char buffer[GFX_COLUMNS * 2];
    _draw_background();
    pal_load_string(_page->title, buffer, sizeof(buffer));
    _draw_title(buffer);
    _create_controls(_page);

    if (0 < id)
    {
        _back.move(GFX_COLUMNS - 32, GFX_LINES - 3);
        _back.draw();
    }
    else
    {
        _back.move(-1, -1);
    }

    _next.draw();
    _cancel.draw();

    _page->proc(SHIZM_ENTERED, NULL, _page->data);
    pal_enable_mouse();
}

int
shiz_direct_click(uint16_t x, uint16_t y)
{
    if (_mouse_down)
    {
        return SHIZ_INCOMPLETE;
    }

    _mouse_down = true;
    if (_is_pressed(_back, x, y))
    {
        return shiz_direct_key(VK_PRIOR);
    }

    if (_is_pressed(_next, x, y))
    {
        return shiz_direct_key(VK_RETURN);
    }

    if (_is_pressed(_cancel, x, y))
    {
        return shiz_direct_key(VK_ESCAPE);
    }

    auto pos = panel_->get_position();
    panel_->click(x - pos.left, y - pos.top);
    return SHIZ_INCOMPLETE;
}

int
shiz_direct_key(uint16_t scancode)
{
    _mouse_down = false;
    if (0 == scancode)
    {
        return SHIZ_INCOMPLETE;
    }

    if (VK_ESCAPE == scancode)
    {
        return SHIZ_CANCEL;
    }

    shiz_textbox_data *textbox = shiz_find_textbox(_page);

    if (VK_RETURN == scancode)
    {
        if (NULL == textbox)
        {
            return SHIZ_OK;
        }

        if (0 >= shiz_check_page(_page, textbox->buffer))
        {
            return SHIZ_OK;
        }

        pal_disable_mouse();
        shiz_direct_animate(false);
        return SHIZ_INCOMPLETE;
    }

    int id = shiz_get_page();
    if ((VK_PRIOR == scancode) && (0 < id))
    {
        pal_disable_mouse();
        shiz_set_page(id - 1);
        return SHIZ_INCOMPLETE;
    }

    if ((VK_F1 <= scancode) && (VK_F7 >= scancode))
    {
        auto option = shiz::get_child<shiz::option>(*panel_, scancode - VK_F1);
        if (option)
        {
            option->click(-1, -1);
        }

        return SHIZ_INCOMPLETE;
    }

    if (VK_F8 == scancode)
    {
        auto checkbox = shiz::get_child<shiz::checkbox>(*panel_);
        if (checkbox)
        {
            checkbox->click(-1, -1);
        }

        return SHIZ_INCOMPLETE;
    }

    panel_->key(scancode);
    return SHIZ_INCOMPLETE;
}

bool
shiz_direct_animate(bool valid)
{
    auto textbox = shiz::get_child<shiz::textbox>(*panel_);
    return textbox ? textbox->animate(valid) : true;
}

void
shiz_direct_set_error(char *message)
{
    auto textbox = shiz::get_child<shiz::textbox>(*panel_);
    if (textbox)
    {
        textbox->alert(message);
    }
}

bool
shiz_refresh_field(shiz_page *page, int id)
{
    if (_page != page)
    {
        return false;
    }

    auto it = panel_->begin() + id;
    (*it)->draw();
    return true;
}
