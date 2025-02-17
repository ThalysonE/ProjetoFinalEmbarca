cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(led_project C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(led_patterns main.c)

target_link_libraries(led_patterns pico_stdlib hardware_pio hardware_pwm)

pico_add_extra_outputs(led_patterns)