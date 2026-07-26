#ifndef SHARIZARD_DRAWING_H
#define SHARIZARD_DRAWING_H

#include <sharizard/base.h>
#include <sharizard/sal.h>

SHIZ_EXTERNC_BEGIN

/**
 * Retrieves the cell dimensions of the text grid.
 *
 * @param[in]  ctx  Drawing context.
 * @param[out] cell Cell dimensions in pixels.
 *
 * @return Negative on error.
 */
extern shizerr
shizd_get_cell_size(_In_opt_ void *ctx, _Out_ shiz_vec2i *cell);

/**
 * Retrieves the viewbox dimensions of the canvas.
 *
 * @param[in]  ctx     Drawing context.
 * @param[out] viewbox Viewbox dimensions in pixels.
 *
 * @return Negative on error.
 */
extern shizerr
shizd_get_viewbox_size(_In_opt_ void *ctx, _Out_ shiz_vec2i *viewbox);

/**
 * Draws a bitmap graphic.
 *
 * @param[in] ctx Drawing context.
 * @param[in] x   Horizontal position in pixels.
 * @param[in] y   Vertical position in pixels.
 * @param[in] bm  Bitmap graphic.
 *
 * @return Negative on error.
 */
extern shizerr
shizd_draw_bitmap(_In_opt_ void *ctx, int x, int y, _In_ const shiz_bitmap *bm);

/**
 * Draws a line.
 *
 * @param[in] ctx    Drawing context.
 * @param[in] x      Origin horizontal position in pixels.
 * @param[in] y      Origin vertical position in pixels.
 * @param[in] extent Line extent vector.
 * @param[in] color  Pen color.
 *
 * @return Negative on error.
 */
extern shizerr
shizd_draw_line(_In_opt_ void         *ctx,
                int                    x,
                int                    y,
                _In_ const shiz_vec2i *extent,
                shiz_color             color);

/**
 * Draws a rectangle border.
 *
 * @param[in] ctx    Drawing context.
 * @param[in] x      Origin horizontal position in pixels.
 * @param[in] y      Origin vertical position in pixels.
 * @param[in] extent Rectangle extent vector.
 * @param[in] color  Pen color.
 *
 * @return Negative on error.
 */
extern shizerr
shizd_draw_rectangle(_In_opt_ void         *ctx,
                     int                    x,
                     int                    y,
                     _In_ const shiz_vec2i *extent,
                     shiz_color             color);

/**
 * Draws a filled rectangle.
 *
 * @param[in] ctx    Drawing context.
 * @param[in] x      Origin horizontal position in pixels.
 * @param[in] y      Origin vertical position in pixels.
 * @param[in] extent Rectangle extent vector.
 * @param[in] color  Brush color.
 *
 * @return Negative on error.
 */
extern shizerr
shizd_fill_rectangle(_In_opt_ void         *ctx,
                     int                    x,
                     int                    y,
                     _In_ const shiz_vec2i *extent,
                     shiz_color             color);

/**
 * Draws text on a grid.
 *
 * @param[in] ctx Drawing context.
 * @param[in] x   Horizontal position in cells.
 * @param[in] y   Vertical position in cells.
 * @param[in] str String (UTF-8 encoded) to be written.
 *
 * @return Negative on error.
 */
extern shizerr
shizd_draw_text(_In_opt_ void     *ctx,
                unsigned           x,
                unsigned           y,
                _In_z_ const char *str);

/**
 * Prevents the host from modifying the drawing surface.
 *
 * @param[in] ctx Drawing context.
 *
 * @return Lock handle on success. Negative on error.
 */
extern shizerr
shizd_lock_surface(_In_opt_ void *ctx);

/**
 * Releases a drawing-surface lock.
 *
 * @param[in] ctx  Drawing context.
 * @param[in] lock Lock handle returned by shizd_lock_surface().
 *
 * @return Negative on error.
 */
extern shizerr
shizd_unlock_surface(_In_opt_ void *ctx, int lock);

SHIZ_EXTERNC_END

#endif // SHARIZARD_DRAWING_H
