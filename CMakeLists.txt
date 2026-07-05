cmake_minimum_required(VERSION 3.20)

project(raw_renderer C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.c
)

add_executable(raw_renderer WIN32 ${SOURCES})

target_include_directories(raw_renderer PRIVATE
    src
)

target_link_libraries(raw_renderer PRIVATE
    opengl32
    gdi32
    user32
)