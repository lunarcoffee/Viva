#ifndef LEXER_HH
#define LEXER_HH

#include <string>

#include "token.hh"

class Lexer {
public:
    std::string code;

    explicit Lexer(std::string code);
    Token next_token();
private:
    int pos;
    std::string cur_char;

    std::string consume_while(const std::string& regex);
    void ignore_spaces();
    void advance();
    void error();
};

#endif
