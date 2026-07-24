#ifndef SHARIZARD_HOST_H
#define SHARIZARD_HOST_H

#include <sharizard/base.h>
#include <sharizard/sal.h>

#if INT_MAX < INT32_MAX
typedef int32_t shiz_ms;
#elif defined(_WIN64)
typedef int64_t shiz_ms;
#else
typedef long shiz_ms;
#endif

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

SHIZ_EXTERNC_END

#endif // SHARIZARD_HOST_H
