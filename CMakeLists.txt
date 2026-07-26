cmake_minimum_required(VERSION 3.24)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    project(Sharizard C RC)
else()
    project(Sharizard C CXX)
endif()


include(CheckIncludeFile)


function(supply_compat_header name)
    check_include_file(${name}.h has_compat_header)
    if(NOT has_compat_header)
        include_directories(inc/compat/${name})
    endif()
endfunction()

supply_compat_header(stdbool)
supply_compat_header(stdint)


add_library(sharizard STATIC)
target_include_directories(sharizard PRIVATE inc)

add_subdirectory(src)

install(TARGETS sharizard DESTINATION .)
