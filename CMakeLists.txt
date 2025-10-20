cmake_minimum_required(VERSION 4.0)
project(passwordmanager)

set(CMAKE_CXX_STANDARD 23)

add_executable(passwordmanager main.cpp
        outputs.h
        outputs.cpp)
