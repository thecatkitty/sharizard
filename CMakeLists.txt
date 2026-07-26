cmake_minimum_required(VERSION 3.24)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    project(Sharizard C RC)
else()
    project(Sharizard C CXX)
endif()

add_library(sharizard STATIC)
target_include_directories(sharizard PRIVATE inc)

add_subdirectory(src)

install(TARGETS sharizard DESTINATION .)
