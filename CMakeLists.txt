cmake_minimum_required(VERSION 4.0)
project(passwordmanager)

set(CMAKE_CXX_STANDARD 23)

add_executable(passwordmanager
        main.cpp
        outputs.h
        outputs.cpp
        decrypt.h
        decrypt.cpp
        database.h
        database.cpp
        encrypt.h
        encrypt.cpp)

find_package(OpenSSL REQUIRED)
target_link_libraries(passwordmanager PRIVATE OpenSSL::Crypto)