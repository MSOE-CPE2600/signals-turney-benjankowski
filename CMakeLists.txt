cmake_minimum_required(VERSION 3.10)

project(signals C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

add_compile_options(-Wall -Werror)

set(CMAKE_C_FLAGS_DEBUG "-g")

add_executable(recv_signal recv_signal.c)
add_executable(send_signal send_signal.c)
add_executable(signal_alarm signal_alarm.c)
add_executable(signal_handler signal_handler.c)
add_executable(signal_segfault signal_segfault.c)
add_executable(signal_sigaction signal_sigaction.c)