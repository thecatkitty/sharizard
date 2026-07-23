#ifndef SHARIZARD_DRAWING_H
#define SHARIZARD_DRAWING_H

#include <sharizard/base.h>
#include <sharizard/sal.h>

SHIZ_EXTERNC_BEGIN

extern shizerr
shizd_get_cell_size(_In_opt_ void *ctx, _Out_ shiz_vec2i *cell);

extern shizerr
shizd_get_viewbox_size(_In_opt_ void *ctx, _Out_ shiz_vec2i *viewbox);

extern shizerr
shizd_draw_bitmap(_In_opt_ void *ctx, int x, int y, _In_ const shiz_bitmap *bm);

extern shizerr
shizd_draw_line(_In_opt_ void         *ctx,
                int                    x,
                int                    y,
                _In_ const shiz_vec2i *extent,
                shiz_color             color);

extern shizerr
shizd_draw_rectangle(_In_opt_ void         *ctx,
                     int                    x,
                     int                    y,
                     _In_ const shiz_vec2i *extent,
                     shiz_color             color);

extern shizerr
shizd_fill_rectangle(_In_opt_ void         *ctx,
                     int                    x,
                     int                    y,
                     _In_ const shiz_vec2i *extent,
                     shiz_color             color);

extern shizerr
shizd_draw_text(_In_opt_ void     *ctx,
                unsigned           x,
                unsigned           y,
                _In_z_ const char *str);

SHIZ_EXTERNC_END

#endif // SHARIZARD_DRAWING_H
