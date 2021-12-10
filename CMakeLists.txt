cmake_minimum_required(VERSION 3.16)
project(CompilerProject)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        main.cpp
        src/Token.cpp
        src/Compiler.cpp
        src/Lexer.cpp
        )

add_executable(CompilerProject ${SOURCE_FILES})
