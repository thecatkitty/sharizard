#include <sharizard.h>

static shiz_field *
_find_field_by_type(shiz_page *page, int type)
{
    int i;
    for (i = 0; i < page->length; i++)
    {
        if (type == page->fields[i].type)
        {
            return page->fields + i;
        }
    }

    return NULL;
}

shiz_field *
shiz_find_checkbox(shiz_page *page)
{
    return _find_field_by_type(page, SHIZFT_CHECKBOX);
}

shiz_textbox_data *
shiz_find_textbox(shiz_page *page)
{
    shiz_field *field = _find_field_by_type(page, SHIZFT_TEXTBOX);
    return field ? (shiz_textbox_data *)field->data : NULL;
}
