cmake_minimum_required(VERSION 2.8.12)

project("SDL examples")

set(CMAKE_BUILD_TYPE Debug)

add_executable(render_poc renderpoc.c)
target_link_libraries(render_poc SDL2)

