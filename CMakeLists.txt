cmake_minimum_required(VERSION 3.14)
project(Viva)

set(CMAKE_CXX_STANDARD 14)
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
)

add_executable(Viva ${SOURCES} src/main.cc)
