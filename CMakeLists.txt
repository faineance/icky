cmake_minimum_required(VERSION 2.8)
project(icky)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
set(CMAKE_BUILD_TYPE Debug)
set(SOURCE_FILES main.c vm.h vm.c debug.h)
add_executable(icky ${SOURCE_FILES})
