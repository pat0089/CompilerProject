cmake_minimum_required(VERSION 3.16)
project(CompilerProject)

set(CMAKE_CXX_STANDARD 14)

set(HEADER_FILES
        src/Token.hpp
        )

set(SOURCE_FILES
        main.cpp
        src/Token.cpp
        )

add_executable(CompilerProject ${SOURCE_FILES})
