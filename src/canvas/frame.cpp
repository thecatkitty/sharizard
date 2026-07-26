#include <algorithm>
#include <cstring>
#include <iterator>
#include <memory>
#include <vector>

#include <sharizard/drawing.h>
#include <sharizard/host.h>
#include <sharizard/input.h>

extern "C"
{
#include "canvas.h"
}

#include "widgets.hpp"

using namespace shiz;

// Screen metrics
static shiz_vec2i _glyph = {0, 0};
static shiz_vec2i _screen = {0, 0};

// Buttons
static shiz_field     _cancel_field{0, SHIZFF_STATIC, SHIZSID_CANCEL};
static shiz_field     _back_field{0, SHIZFF_STATIC, SHIZSID_BACK};
static shiz_field     _next_field{0, SHIZFF_STATIC, SHIZSID_NEXT};
static canvas::button _cancel{_cancel_field};
static canvas::button _back{_back_field};
static canvas::button _next{_next_field};
static bool           _mouse_down;

// Page state
static shiz_page *_page;

std::unique_ptr<canvas::panel> panel_{};

void
shiz_canvas_init_frame(const shiz_wizard *wizard)
{
    shizd_get_viewbox_size(nullptr, &_screen);
    shizd_get_cell_size(nullptr, &_glyph);

    auto bar = shiz_vec2i{_screen.x, 3 * _glyph.y + 1};
    shizd_fill_rectangle(nullptr, 0, _screen.y - bar.y, &bar, SHIZ_COLOR_BLACK);

    auto brand = wizard->brand_text;
    for (int y = 22; y <= 24; ++y)
    {
        char line[TEXT_WIDTH / 2 + 1];
        auto line_end = strchr(brand, '\n');
        auto available =
            line_end ? static_cast<size_t>(line_end - brand) : strlen(brand);
        auto line_length = std::min(available, sizeof(line) - 1);
        memcpy(line, brand, line_length);
        line[line_length] = '\0';
        shizd_draw_text(nullptr, 1, y, line);

        if (line_end)
        {
            brand = line_end + 1;
        }
        else
        {
            break;
        }
    }

    _next.move(SHIZ_CANVAS_COLUMNS - 22, SHIZ_CANVAS_ROWS - 3);
    _cancel.move(SHIZ_CANVAS_COLUMNS - 11, SHIZ_CANVAS_ROWS - 3);
}

static void
_draw_title(char *title)
{
    auto bar = shiz_vec2i{_screen.x, _glyph.y + 1};
    shizd_fill_rectangle(nullptr, 0, 0, &bar, SHIZ_COLOR_BLACK);
    shizd_draw_text(nullptr, 1, 0, title);
}

static void
_draw_background(void)
{
    auto bg = shiz_vec2i{_screen.x, (SHIZ_CANVAS_ROWS - 4) * _glyph.y};
    shizd_fill_rectangle(nullptr, 0, _glyph.y, &bg, SHIZ_COLOR_WHITE);

    auto footer = shiz_vec2i{_screen.x / 2, 3 * _glyph.y};
    shizd_fill_rectangle(nullptr, footer.x, _screen.y - footer.y, &footer,
                         SHIZ_COLOR_BLACK);
}

static bool
_is_pressed(const canvas::widget &widget, uint16_t msx, uint16_t msy)
{
    auto pos = widget.get_absolute_position();
    if (0 > pos.x)
    {
        return false;
    }

    auto size = widget.get_size();
    if ((pos.x > int(msx)) || ((pos.x + size.x) <= int(msx)))
    {
        return false;
    }

    if ((pos.y > int(msy)) || ((pos.y + size.y) <= int(msy)))
    {
        return false;
    }

    return true;
}

static void
_create_controls(shiz_page *page)
{
    panel_ = std::make_unique<canvas::panel>(*page);

    int x, y;
    _mouse_down = SHIZ_MOUSE_LBUTTON & shizi_get_mouse(nullptr, &x, &y);

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
            auto &label = panel_->create<canvas::label>(*field);
            if (SHIZFF_FOOTER & field->flags)
            {
                label.move(1, SHIZ_CANVAS_ROWS - 5);
                label.draw();
            }
            else
            {
                label.move(1, cy);
                label.draw();
                cy = label.get_position().y + label.get_size().y;
            }
        }

        if (SHIZFT_TEXTBOX == field->type)
        {
            auto &textbox = panel_->create<canvas::textbox>(*field);
            textbox.move(1, cy);
            textbox.draw();
            cy = textbox.get_position().y + textbox.get_size().y;
        }

        if (!has_checkbox && (SHIZFT_CHECKBOX == field->type))
        {
            has_checkbox = true;

            auto &checkbox = panel_->create<canvas::checkbox>(*field);
            checkbox.move(1, SHIZ_CANVAS_ROWS - 5);
            checkbox.draw();
        }

        if (SHIZFT_OPTION == field->type)
        {
            auto &option = panel_->create<canvas::option>(*field);
            option.move(1, cy);
            option.draw();
            cy = option.get_position().y + option.get_size().y;
        }

        if (SHIZFT_BITMAP == field->type)
        {
            auto &bitmap = panel_->create<canvas::bitmap>(*field);
            bitmap.move(1, cy);
            bitmap.draw();
            cy = bitmap.get_position().y + bitmap.get_size().y;
        }
    }
}

void
shiz_canvas_enter_page(shiz_page *pages, int id)
{
    _page = pages + id;
    _page->proc(SHIZM_INIT, NULL, _page->data);

    char buffer[SHIZ_CANVAS_COLUMNS * 2];
    auto lock = shizd_lock_surface(nullptr);
    _draw_background();
    shizh_load_string(nullptr, _page->title, buffer, sizeof(buffer));
    _draw_title(buffer);
    _create_controls(_page);

    if (0 < id)
    {
        _back.move(SHIZ_CANVAS_COLUMNS - 32, SHIZ_CANVAS_ROWS - 3);
        _back.draw();
    }
    else
    {
        _back.move(-1, -1);
    }

    _next.draw();
    _cancel.draw();

    _page->proc(SHIZM_ENTERED, NULL, _page->data);
    shizd_unlock_surface(nullptr, lock);
}

int
shiz_canvas_click(int x, int y)
{
    if (_mouse_down)
    {
        return SHIZ_INCOMPLETE;
    }

    _mouse_down = true;
    if (_is_pressed(_back, x, y))
    {
        return shiz_canvas_key(SHIZK_PAGEUP);
    }

    if (_is_pressed(_next, x, y))
    {
        return shiz_canvas_key(SHIZK_RETURN);
    }

    if (_is_pressed(_cancel, x, y))
    {
        return shiz_canvas_key(SHIZK_ESCAPE);
    }

    auto pos = panel_->get_absolute_position();
    panel_->click(x - pos.x, y - pos.y);
    return SHIZ_INCOMPLETE;
}

int
shiz_canvas_key(uint16_t scancode)
{
    _mouse_down = false;
    if (0 == scancode)
    {
        return SHIZ_INCOMPLETE;
    }

    if (SHIZK_ESCAPE == scancode)
    {
        return SHIZ_CANCEL;
    }

    shiz_textbox_data *textbox = shiz_find_textbox(_page);

    if (SHIZK_RETURN == scancode)
    {
        if (NULL == textbox)
        {
            return SHIZ_OK;
        }

        if (0 >= shiz_check_page(_page, textbox->buffer))
        {
            return SHIZ_OK;
        }

        shiz_canvas_animate(false);
        return SHIZ_INCOMPLETE;
    }

    int id = shiz_get_page();
    if ((SHIZK_PAGEUP == scancode) && (0 < id))
    {
        shiz_set_page(id - 1);
        return SHIZ_INCOMPLETE;
    }

    if ((SHIZK_F1 <= scancode) && (SHIZK_F7 >= scancode))
    {
        auto option =
            canvas::get_child<canvas::option>(*panel_, scancode - SHIZK_F1);
        if (option)
        {
            option->click(-1, -1);
        }

        return SHIZ_INCOMPLETE;
    }

    if (SHIZK_F8 == scancode)
    {
        auto checkbox = canvas::get_child<canvas::checkbox>(*panel_);
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
shiz_canvas_animate(bool valid)
{
    auto textbox = canvas::get_child<canvas::textbox>(*panel_);
    return textbox ? textbox->animate(valid) : true;
}

void
shiz_canvas_set_error(char *message)
{
    auto textbox = canvas::get_child<canvas::textbox>(*panel_);
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
