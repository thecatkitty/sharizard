cmake_minimum_required(VERSION 3.24)

project(Sharizard C CXX)


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
target_include_directories(sharizard PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>")

add_subdirectory(src)

install(TARGETS sharizard DESTINATION .)
