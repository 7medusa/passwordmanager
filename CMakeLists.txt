cmake_minimum_required(VERSION 4.0)
project(passwordmanager)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(passwordmanager
        Qt/main.cpp
        backend/back.h
        backend/back.cpp
        backend/decrypt.h
        backend/decrypt.cpp
        backend/database.h
        backend/database.cpp
        backend/encrypt.h
        backend/encrypt.cpp
        backend/init.cpp
        backend/init.h
        libs/tiny-AES-c/aes.c
        Qt/login.h
        Qt/login.cpp
        Qt/window.h
        Qt/window.cpp
        Qt/mainMenu.h
        Qt/mainMenu.cpp
)

find_package(OpenSSL REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

target_link_libraries(passwordmanager PRIVATE Qt6::Widgets)
target_link_libraries(passwordmanager PRIVATE OpenSSL::Crypto)
target_include_directories(passwordmanager PRIVATE /home/medusa/projekte/studium/libs/tiny-AES-c/aes.hpp)