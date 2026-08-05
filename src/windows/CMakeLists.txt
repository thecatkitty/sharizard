if(NOT DEFINED WINVER)
    set(WINVER 0x0400)
endif()
math(EXPR WINVER_MAJOR "${WINVER} >> 8")
math(EXPR WINVER_MINOR "${WINVER} & 0xFF")

message(STATUS "Building for Windows ${WINVER_MAJOR}.${WINVER_MINOR}")

target_sources(sharizard
    PRIVATE
        windows.c
    INTERFACE
        prompt.rc)
