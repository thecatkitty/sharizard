#ifndef WINDOWS_WINUTILS_H
#define WINDOWS_WINUTILS_H

#include <windows.h>

#include <sharizard/base.h>

#if defined(_MSC_VER) && (_MSC_VER < 1800)
#define inline __inline
#endif

inline static uint16_t
windows_get_version(void)
{
#if defined(_MSC_VER) && (_MSC_VER >= 1900)
#pragma warning(push)
#pragma warning(disable : 28159)
#endif
    WORD version = LOWORD(GetVersion());
#if defined(_MSC_VER) && (_MSC_VER >= 1900)
#pragma warning(pop)
#endif
    return (LOBYTE(version) << 8) | HIBYTE(version);
}

inline static bool
windows_is_at_least(uint16_t ver)
{
    return ver <= windows_get_version();
}

inline static bool
windows_is_less_than(uint16_t ver)
{
    return ver > windows_get_version();
}

inline static FARPROC
windows_get_proc(const char *module, const char *name)
{
    HMODULE hmodule = GetModuleHandleA(module);
    return hmodule ? GetProcAddress(hmodule, name) : NULL;
}

#define winver_or_windows_is_at_least(ver)                                     \
    ((WINVER >= (ver)) || windows_is_at_least((ver)))

#define winver_and_windows_is_less_than(ver)                                   \
    ((WINVER < (ver)) && windows_is_less_than((ver)))

#define windows_is_less_than_2000() winver_and_windows_is_less_than(0x0500)
#define windows_is_at_least_vista() winver_or_windows_is_at_least(0x0600)

#endif // WINDOWS_WINUTILS_H
