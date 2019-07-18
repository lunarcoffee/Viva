#include <iostream>
#include <fstream>
#include <sstream>

#include "lexer.hh"
#include "parser/ast.hh"

int main() {
    std::stringstream code_stream;
    std::ifstream file{"../data/test1.cpp"};
    code_stream << file.rdbuf();
    auto code{code_stream.str()};

    Lexer lexer{code};
    Token token;
    while ((token = lexer.next_token()).type != TT::END)
        std::cout << token.value << "\n";

    Lexer lex2(code);
    AST ast{std::move(lex2)};
    ast.construct();
}
