cmake_minimum_required(VERSION 3.6)
project(PROJET)

set(CMAKE_C_STANDARD 99)
set(SOURCE_FILES main.c cmake-build-debug/structs.h)

set(SOURCE_FILES main.c)
add_executable(PROJET ${SOURCE_FILES} main.c)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
