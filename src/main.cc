#include <iostream>

#include "lexer.hh"
#include "parser/ast.hh"

int main() {
    std::string code;
    while (true) {
        std::cout << ":> ";
        std::getline(std::cin, code);

        if (code.empty())
            continue;
        if (code == ":quit")
            return 0;

        Lexer lexer(code);
        Token token;
        while ((token = lexer.next_token()).type != TT::END)
            std::cout << token.value << "\n";

        std::cout << "\nParser results:";

        Lexer lex2(code);
        AST ast{std::move(lex2)};
        ast.construct();
    }
}
