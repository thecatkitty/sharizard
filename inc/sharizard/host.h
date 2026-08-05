#ifndef SHARIZARD_HOST_H
#define SHARIZARD_HOST_H

#include <sharizard/base.h>
#include <sharizard/sal.h>

/**
 * Sharizard library-defined localized string identifier.
 */
enum shizsid
{
    SHIZSID_CANCEL = -1, //!< "Cancel".
    SHIZSID_BACK = -2,   //!< "Back".
    SHIZSID_NEXT = -3,   //!< "Next".
};

SHIZ_EXTERNC_BEGIN

/**
 * Retrieves the current monotonic clock value.
 *
 * @param[in] ctx Host context.
 *
 * @return Milliseconds elapsed since the host context was created.
 */
extern shiz_ms
shizh_get_clock(_In_opt_ void *ctx);

/**
 * Loads a localized string from the application resources.
 *
 * Copies at most (buffsz - 1) bytes of the referenced string, preserving
 * complete UTF-8 sequences. The output is always null-terminated when buffsz is
 * greater than 0.
 *
 * @param[in]  ctx    Host context.
 * @param[in]  id     Localized string identifier. Negative values refer to
 *                    library-defined strings.
 * @param[out] buff   Output buffer. May be NULL when buffsz is 0.
 * @param[in]  buffsz Size of the output buffer in bytes.
 *
 * @return Number of bytes stored in buff (excluding the terminating null
 *         character) when buffsz is greater than 0. If buffsz is 0, returns
 *         the length of the referenced string in bytes. Negative on error.
 */
extern shizerr
shizh_load_string(_In_opt_ void                   *ctx,
                  int                              id,
                  _Out_writes_opt_z_(buffsz) char *buff,
                  size_t                           buffsz);

SHIZ_EXTERNC_END

#endif // SHARIZARD_HOST_H
