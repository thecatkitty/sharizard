#include <algorithm>
#include <cstring>
#include <tuple>

#include <sharizard/drawing.h>

#include "widgets.hpp"

using namespace shiz::canvas;

namespace
{
std::pair<shiz_vec2i, shiz_vec2i>
get_caret(int x, int y, int position)
{
    shiz_vec2i glyph;
    shizd_get_cell_size(nullptr, &glyph);
    return {{(x + position + 1) * glyph.x, (y + 1) * glyph.y}, {1, glyph.y}};
}

std::pair<shiz_vec2i, shiz_vec2i>
get_field(int x, int y, shiz_vec2i size)
{
    shiz_vec2i glyph;
    shizd_get_cell_size(nullptr, &glyph);
    return {{x * glyph.x, (y + 1) * glyph.y - (glyph.x / 2)},
            {size.x * glyph.x, glyph.y + glyph.x}};
}
} // namespace

enum
{
    STATE_PROMPT,
    STATE_INVALID1,
    STATE_INVALID2,
    STATE_INVALID3,
};

textbox::textbox(shiz_field &field)
    : widget{field}, blink_start_{}, caret_period_{}, caret_counter_{},
      caret_visible_{true}, caret_position_{}, state_{STATE_PROMPT}
{
    auto &textbox = *reinterpret_cast<shiz_textbox_data *>(field.data);
    if (0 == textbox.length)
    {
        textbox.buffer[0] = 0;
    }

    size_t field_width = GFX_COLUMNS / 2 - 1;
    if (field_width < textbox.capacity)
    {
        field_width = textbox.capacity;
    }

    caret_position_ = textbox.length;

    size_.x = field_width + 2;
    size_.y = 5;
}

void
textbox::draw()
{
    auto &page = *get_page();
    auto &textbox = *reinterpret_cast<shiz_textbox_data *>(field_.data);

    auto pos = get_absolute_position();
    auto field = get_field(pos.x, pos.y, size_);
    shizd_draw_rectangle(nullptr, field.first.x, field.first.y, &field.second,
                         (0 < shiz_check_page(&page, textbox.buffer))
                             ? SHIZ_COLOR_GRAY
                             : SHIZ_COLOR_BLACK);
    shizd_fill_rectangle(nullptr, field.first.x, field.first.y, &field.second,
                         SHIZ_COLOR_WHITE);
    shizd_draw_text(nullptr, position_.x + 1, position_.y + 1, textbox.buffer);

    caret_period_ = palpp_get_ticks(500);
    caret_counter_ = palpp_get_counter();
}

bool
textbox::animate(bool valid)
{
    if (!valid && (STATE_PROMPT == state_))
    {
        state_ = STATE_INVALID1;
        blink_start_ = palpp_get_counter();
        return false;
    }

    auto pos = get_absolute_position();
    auto field = get_field(pos.x, pos.y, size_);
    if (STATE_INVALID1 == state_)
    {
        if (palpp_get_counter() > blink_start_ + palpp_get_ticks(63))
        {
            shizd_draw_rectangle(nullptr, field.first.x, field.first.y,
                                 &field.second, SHIZ_COLOR_GRAY);
            state_ = STATE_INVALID2;
        }

        return false;
    }

    if (STATE_INVALID2 == state_)
    {
        if (palpp_get_counter() > blink_start_ + palpp_get_ticks(126))
        {
            shizd_draw_rectangle(nullptr, field.first.x, field.first.y,
                                 &field.second, SHIZ_COLOR_BLACK);
            state_ = STATE_INVALID3;
        }

        return false;
    }

    if (STATE_INVALID3 == state_)
    {
        if (palpp_get_counter() > blink_start_ + palpp_get_ticks(189))
        {
            shizd_draw_rectangle(nullptr, field.first.x, field.first.y,
                                 &field.second, SHIZ_COLOR_GRAY);
            draw();
            state_ = STATE_PROMPT;
            pal_enable_mouse();
        }

        return false;
    }

    if (palpp_get_counter() > caret_counter_ + caret_period_)
    {
        auto pos = get_absolute_position();
        auto caret = get_caret(pos.x, pos.y, caret_position_);
        shizd_draw_line(nullptr, caret.first.x, caret.first.y, &caret.second,
                        caret_visible_ ? SHIZ_COLOR_BLACK : SHIZ_COLOR_WHITE);
        caret_counter_ = palpp_get_counter();
        caret_visible_ = !caret_visible_;
    }

    return true;
}

void
textbox::alert(char *message)
{
    shiz_vec2i glyph;
    shizd_get_cell_size(nullptr, &glyph);

    auto bg = shiz_vec2i{size_.x * glyph.x, 3 * glyph.y};
    shizd_fill_rectangle(nullptr, 0, (position_.y + 3) * glyph.y, &bg,
                         SHIZ_COLOR_WHITE);

    auto pos = get_absolute_position();
    shiz_canvas_print(pos.y + 3, message);
}

int
textbox::click(int x, int y)
{
    if (2 < y)
    {
        return 0;
    }

    auto &textbox = *reinterpret_cast<shiz_textbox_data *>(field_.data);

    int cursor = std::max(0, std::min(int(textbox.length), x - 1));
    if (caret_position_ != cursor)
    {
        caret_position_ = cursor;
        pal_disable_mouse();
        draw();
        pal_enable_mouse();
    }

    return 0;
}

int
textbox::key(int scancode)
{
    auto &textbox = *reinterpret_cast<shiz_textbox_data *>(field_.data);

    pal_disable_mouse();

    shiz_vec2i glyph;
    shizd_get_cell_size(nullptr, &glyph);

    auto pos = get_absolute_position();
    auto caret = get_caret(pos.x, pos.y, caret_position_);
    shizd_draw_line(nullptr, caret.first.x, caret.first.y, &caret.second,
                    SHIZ_COLOR_WHITE);

    if ((VK_LEFT == scancode) && (0 < caret_position_))
    {
        caret_position_--;
        draw();
    }

    if ((VK_RIGHT == scancode) && (int(textbox.length) > caret_position_))
    {
        caret_position_++;
        draw();
    }

    if ((VK_BACK == scancode) && (0 < caret_position_))
    {
        std::memmove(textbox.buffer + caret_position_ - 1,
                     textbox.buffer + caret_position_,
                     textbox.length - caret_position_);
        caret_position_--;
        textbox.length--;
        textbox.buffer[textbox.length] = 0;
        draw();
    }

    if ((VK_DELETE == scancode) && (int(textbox.length) > caret_position_))
    {
        std::memmove(textbox.buffer + caret_position_,
                     textbox.buffer + caret_position_ + 1,
                     textbox.length - caret_position_ - 1);
        textbox.length--;
        textbox.buffer[textbox.length] = 0;
        draw();
    }

    if (((' ' == scancode) || (VK_OEM_MINUS == scancode) ||
         ((VK_DELETE < scancode) && (VK_F1 > scancode))) &&
        (textbox.length < textbox.capacity))
    {
        std::memmove(textbox.buffer + caret_position_ + 1,
                     textbox.buffer + caret_position_,
                     textbox.length - caret_position_);
        textbox.buffer[caret_position_] =
            (VK_OEM_MINUS == scancode) ? '-' : (scancode & 0xFF);
        caret_position_++;
        textbox.length++;
        textbox.buffer[textbox.length] = 0;
        draw();
    }

    caret = get_caret(pos.x, pos.y, caret_position_);
    shizd_draw_line(nullptr, caret.first.x, caret.first.y, &caret.second,
                    SHIZ_COLOR_BLACK);
    pal_enable_mouse();
    return 0;
}
