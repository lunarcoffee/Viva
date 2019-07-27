#include <iostream>
#include <fstream>
#include <sstream>

#include "lexer.hh"
#include "parser/ast.hh"
#include "gen.hh"

int main() {
    std::stringstream ss;
    std::ifstream file{"../data/test.viv"};
    ss << file.rdbuf();

    // Get code and strip trailing newlines to avoid lexer errors (fix this later).
    auto code{ss.str()};
    while (code[code.size() - 1] == '\n')
        code.pop_back();

    // Display all tokens.
    Lexer lexer{code};
    Token token;
    while ((token = lexer.next_token()).type != TT::END)
        std::cout << token.value << "\n";

    // Reset lexer, and run the code generator with an AST generator for the lexer.
    Lexer lex2{code};
    AST ast{std::move(lex2)};
    std::ofstream output{"../data/test.asm"};
    Generator gen{std::move(ast), output};
    gen.gen();
}
