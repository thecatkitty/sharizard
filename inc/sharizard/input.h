#ifndef SHARIZARD_INPUT_H
#define SHARIZARD_INPUT_H

#include <sharizard/base.h>
#include <sharizard/sal.h>

/**
 * Key code definitions.
 *
 * Codes 0x020 to 0x07e correspond to ASCII characters.
 */
#define SHIZK_BACKSPACE 0x008 //!< Backspace.
#define SHIZK_RETURN    0x00d //!< Enter (Return).
#define SHIZK_ESCAPE    0x01b //!< Esc.
#define SHIZK_DELETE    0x07f //!< Delete.
#define SHIZK_F1        0x83a //!< F1.
#define SHIZK_F2        0x83b //!< F2.
#define SHIZK_F3        0x83c //!< F3.
#define SHIZK_F4        0x83d //!< F4.
#define SHIZK_F5        0x83e //!< F5.
#define SHIZK_F6        0x83f //!< F6.
#define SHIZK_F7        0x840 //!< F7.
#define SHIZK_F8        0x841 //!< F8.
#define SHIZK_PAGEUP    0x84b //!< Page up.
#define SHIZK_RIGHT     0x84f //!< Right arrow.
#define SHIZK_LEFT      0x850 //!< Left arrow.
#define SHIZK_KP_MINUS  0x856 //!< Numeric keypad minus.

/**
 * Mouse button state definitions.
 */
#define SHIZ_MOUSE_LBUTTON (1 << 0) //!< Left mouse button pressed.

SHIZ_EXTERNC_BEGIN

/**
 * Retrieves and consumes the next pending key.
 *
 * @param[in] ctx Input context.
 *
 * @return Key code, or zero if no key is available.
 */
extern uint16_t
shizi_get_key(_In_opt_ void *ctx);

/**
 * Retrieves the current mouse position and button state. Position coordinates
 * are negative when the cursor is outside the canvas.
 *
 * @param[in]  ctx Input context.
 * @param[out] x   Horizontal mouse position inside the grid.
 * @param[out] y   Vertical mouse position inside the grid.
 *
 * @return Mouse button state flags (SHIZ_MOUSE_*).
 */
extern uint16_t
shizi_get_mouse(_In_opt_ void *ctx, _Out_ int *x, _Out_ int *y);

SHIZ_EXTERNC_END

#endif // SHARIZARD_INPUT_H
