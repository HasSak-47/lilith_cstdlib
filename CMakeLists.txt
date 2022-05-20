cmake_minimum_required(VERSION 3.8)
project(lilith_stdlib VERSION 1.0.0)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_FLAGS "-std=c17 -lm")

find_package(Curses REQUIRED)
include_directories("include" "/usr/include")
file(GLOB_RECURSE COMPILATION_UNITS "src/*.c")

add_executable(lil ${COMPILATION_UNITS})
target_link_libraries(lil ${CURSES_LIBRARIES})
