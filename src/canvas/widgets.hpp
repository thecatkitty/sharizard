#pragma once

#include <memory>
#include <vector>

#include <sharizard/base.h>

extern "C"
{
#include "canvas.h"
}

namespace shiz
{
namespace canvas
{

extern shiz_field null_field;

struct widget
{
    widget(const widget &) = delete;
    virtual ~widget() = default;

    widget(const shiz_page &page)
        : page_{&page}, field_{null_field}, position_{}, size_{},
          parent_{nullptr}
    {
    }

    widget(shiz_field &field)
        : page_{}, field_{field}, position_{}, size_{}, parent_{nullptr}
    {
    }

    shiz_field
    get_model() const
    {
        return field_;
    }

    const shiz_page *
    get_page() const
    {
        return parent_ ? parent_->get_page() : page_;
    }

    void
    move(int left, int top)
    {
        position_ = shiz_vec2i{left, top};
    }

    shiz_vec2i
    get_absolute_position() const
    {
        return parent_ ? shiz_vec2i{parent_->position_.x + position_.x,
                                    parent_->position_.y + position_.y}
                       : position_;
    }

    shiz_vec2i
    get_position() const
    {
        return position_;
    }

    shiz_vec2i
    get_size() const
    {
        return size_;
    }

    void
    set_parent(widget *parent)
    {
        parent_ = parent;
    }

    virtual void
    draw()
    {
    }

    virtual int
    click(int x, int y)
    {
        return 0;
    }

    virtual int
    key(int scancode)
    {
        return 0;
    }

  protected:
    const shiz_page *page_;
    shiz_field      &field_;
    shiz_vec2i       position_;
    shiz_vec2i       size_;
    widget          *parent_;
};

using widget_ptr = std::unique_ptr<widget>;

struct bitmap : widget
{
    bitmap(shiz_field &field);

    void
    draw() override;
};

struct button : widget
{
    button(shiz_field &field);

    void
    draw() override;

    int
    click(int x, int y) override;
};

struct checkbox : widget
{
    checkbox(shiz_field &field);

    void
    draw() override;

    int
    click(int x, int y) override;

  private:
    void
    mark(bool checked);

    shiz_vec2i box_position_;
    shiz_vec2i box_size_;
};

struct label : widget
{
    label(shiz_field &field) : widget{field}
    {
    }

    void
    draw() override;

    int
    click(int x, int y) override;
};

struct option : widget
{
    option(shiz_field &field);

    void
    draw() override;

    int
    click(int x, int y) override;

  private:
    void
    mark(bool checked);

    void
    set(bool checked);
};

struct panel : widget
{
    panel(const shiz_page &page) : widget{page}, children_{}
    {
    }

    void
    draw() override;

    int
    click(int x, int y) override;

    int
    key(int scancode) override;

    template <typename T, typename... Args>
    T &
    create(Args &&...args)
    {
        auto child = std::make_unique<T>(std::forward<Args>(args)...);
        child->set_parent(this);
        return *reinterpret_cast<T *>(
            children_.insert(children_.end(), std::move(child))->get());
    }

    std::vector<widget_ptr>::iterator
    begin()
    {
        return children_.begin();
    }

    std::vector<widget_ptr>::iterator
    end()
    {
        return children_.end();
    }

    std::vector<widget_ptr>::iterator
    get_child_by_type(int type, size_t nth = 0);

  private:
    std::vector<widget_ptr> children_;
};

struct textbox : widget
{
    textbox(shiz_field &field);

    void
    draw() override;

    int
    click(int x, int y) override;

    int
    key(int scancode) override;

    bool
    animate(bool valid);

    void
    alert(char *message);

  private:
    uint32_t blink_start_;
    uint32_t caret_period_;
    uint32_t caret_counter_;
    bool     caret_visible_;
    int      caret_position_;
    int      state_;
};

template <typename T> struct field_type
{
    static const int type = SHIZFT_SEPARATOR;
};
template <> struct field_type<checkbox>
{
    static const int type = SHIZFT_CHECKBOX;
};

template <> struct field_type<label>
{
    static const int type = SHIZFT_LABEL;
};

template <> struct field_type<option>
{
    static const int type = SHIZFT_OPTION;
};

template <> struct field_type<textbox>
{
    static const int type = SHIZFT_TEXTBOX;
};

template <typename T>
T *
get_child(panel &panel, size_t nth = 0)
{
    auto it = panel.get_child_by_type(field_type<T>::type, nth);
    return (panel.end() == it) ? nullptr : reinterpret_cast<T *>(it->get());
}

} // namespace canvas
} // namespace shiz
