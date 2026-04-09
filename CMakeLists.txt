cmake_minimum_required(VERSION 4.0)
project(passwordmanager)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(passwordmanager
        main.cpp
        #backend/back.h
        #backend/back.cpp
        #backend/decrypt.h
        #backend/decrypt.cpp
        #backend/database.h
        #backend/database.cpp
        #backend/encrypt.h
        #backend/encrypt.cpp
        #backend/init.cpp
        #backend/init.h
        libs/tiny-AES-c/aes.c
        Qt/login.h
        Qt/login.cpp
        Qt/window.h
        Qt/window.cpp
        Qt/mainMenu.h
        Qt/mainMenu.cpp
        sqlBackend/masterpassword.h
        sqlBackend/masterpassword.cpp
        sqlBackend/sql.h
        sqlBackend/sql.cpp
        Qt/entrie.h
        Qt/entrie.cpp
)

find_package(OpenSSL REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(SQLite3 REQUIRED)

target_link_libraries(passwordmanager PRIVATE Qt6::Widgets)
target_link_libraries(passwordmanager PRIVATE OpenSSL::Crypto)
target_link_libraries(passwordmanager PRIVATE SQLite::SQLite3)
target_include_directories(passwordmanager PRIVATE /home/medusa/projekte/studium/libs/tiny-AES-c/aes.hpp)