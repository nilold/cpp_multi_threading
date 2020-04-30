cmake_minimum_required(VERSION 3.16)
project(multi_thread)

set(CMAKE_CXX_STANDARD 14)

add_executable(multi_thread main.cpp simple_thread.h mutex.h)