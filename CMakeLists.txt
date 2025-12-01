cmake_minimum_required(VERSION 4.0)
project(passwordmanager)

set(CMAKE_CXX_STANDARD 23)

add_executable(passwordmanager
        main.cpp
        decrypt.h
        decrypt.cpp
        database.h
        database.cpp
        encrypt.h
        encrypt.cpp
        libs/tiny-AES-c/aes.c
        init.cpp
        init.h)

find_package(OpenSSL REQUIRED)
target_link_libraries(passwordmanager PRIVATE OpenSSL::Crypto)
target_include_directories(passwordmanager PRIVATE /home/medusa/projekte/studium/libs/tiny-AES-c/aes.hpp)