cmake_minimum_required(VERSION 3.14)
project(Viva)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

set(
    SOURCES

    src/lexer.cc
    src/lexer.hh

    src/token.cc
    src/token.hh

    src/parser/ast.cc
    src/parser/ast.hh
    src/parser/nodes.cc
    src/parser/nodes.hh

    src/gen.cc
    src/gen.hh
)

add_executable(Viva ${SOURCES} src/main.cc)
