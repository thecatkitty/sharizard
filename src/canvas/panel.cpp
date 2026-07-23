#include <algorithm>

#include "widgets.hpp"

using namespace shiz::canvas;

void
panel::draw()
{
    for (auto &child : children_)
    {
        child->draw();
    }
}

int
panel::click(int x, int y)
{
    for (auto &child : children_)
    {
        auto pos = child->get_absolute_position();
        if ((pos.x > x) || ((pos.x + size_.x) <= x))
        {
            continue;
        }

        if ((pos.y > y) || ((pos.y + size_.y) <= y))
        {
            continue;
        }

        auto status = child->click(x - pos.x, y - pos.y);
        if (0 != status)
        {
            return status;
        }
    }

    return 0;
}

int
panel::key(int scancode)
{
    for (auto &child : children_)
    {
        auto status = child->key(scancode);
        if (0 != status)
        {
            return status;
        }
    }

    return 0;
}

std::vector<widget_ptr>::iterator
panel::get_child_by_type(int type, size_t nth)
{
    return std::find_if(
        children_.begin(), children_.end(), [&](const widget_ptr &widget) {
            return (type == widget->get_model().type) && (0 == nth--);
        });
}

shiz_field shiz::canvas::null_field{};
