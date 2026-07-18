#include <string.h>

#include "canvas.h"

#define MAX_LINE_SIZE (2 * GFX_COLUMNS)

typedef struct
{
    uint8_t upper;
    int     length;
} sequence_range;

static const sequence_range SEQUENCE_RANGES[] = {
    {0x00, 0}, {0xbf, 1 /* Including stray continuation */},
    {0xdf, 2}, {0xef, 3},
    {0xf7, 4}, {0xff, 1 /* Wrong preamble */},
};

static int
_get_sequence_length(const char *str)
{
    const uint8_t         byte = *(const uint8_t *)str;
    const sequence_range *range = SEQUENCE_RANGES;

    while (byte > range->upper)
    {
        range++;
    }

    return range->length;
}

static int
_measure_span(const char *str, size_t span)
{
    const char *end = str + span;
    int         length;

    for (length = 0; str < end; length++)
    {
        str += _get_sequence_length(str);
    }

    return length;
}

static int
_copy_text(char *dst, const char *src, size_t length)
{
    int size = 0;

    for (int i = 0; i < length; i++)
    {
        int seq = _get_sequence_length(src + size);
        memcpy(dst + size, src + size, seq);
        size += seq;
    }

    dst[size] = 0;
    return size;
}

static int
_wrap(char *dst, const char *src, size_t width, char delimiter)
{
    int chars = 0;

    const char *psrc = src;
    char       *pdst = dst;
    while (*psrc && (chars <= width))
    {
        if (delimiter == *psrc)
        {
            *pdst = 0;
            return psrc - src + 1;
        }

        size_t word_span = strcspn(psrc, " \n");
        int    word_length = _measure_span(psrc, word_span);
        if (width < chars + word_length)
        {
            if (src == psrc)
            {
                return _copy_text(dst, src, width);
            }

            break;
        }

        memcpy(pdst, psrc, word_span);
        psrc += word_span;
        pdst += word_span;
        chars += word_length;

        while ((' ' == *psrc) && (chars < width))
        {
            *pdst = *psrc;
            psrc++;
            pdst++;
            chars++;
        }

        if (chars == width)
        {
            while (' ' == *psrc)
            {
                psrc++;
            }
        }
    }

    *pdst = 0;
    return psrc - src;
}

void
shiz_canvas_load_string(shiz_field *field, char *buff, size_t length)
{
    if (SHIZFF_DYNAMIC & field->flags)
    {
        strncpy(buff, (const char *)field->data, length);
    }
    else
    {
        pal_load_string(field->data, buff, length);
    }
}

int
shiz_canvas_print(int top, char *text)
{
    const char *fragment = text;
    char        line_buff[MAX_LINE_SIZE + 1];

    int line = 0;
    while (*fragment)
    {
        fragment += _wrap(line_buff, fragment, TEXT_WIDTH, '\n');
        if (!gfx_draw_text(line_buff, 1, top + line))
        {
            return -1;
        }
        line++;
    }

    return line;
}
