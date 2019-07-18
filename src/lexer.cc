#include <iostream>
#include <regex>
#include <stdexcept>

#include "lexer.hh"

Lexer::Lexer(std::string code) : code(code), pos(0), cur_char(std::string(1, code[0])) {}

Token Lexer::next_token() {
    while (cur_char != "<EOF>") {
        ignore_spaces();

        if (isdigit(cur_char[0]))
            return Token(TT::INT, consume_while(R"(\d)"));

        if (isalpha(cur_char[0]) || cur_char == "_") {
            std::string str{consume_while(R"(\w)")};
            return Token(str == "int" || str == "return" ? TT::KEYWORD : TT::ID, std::move(str));
        }

        Token token;
        switch (cur_char[0]) {
        case ';':
            token = Token(TT::SEMICOLON, ";");
            break;
        case '{':
            token = Token(TT::LBRACE, "{");
            break;
        case '}':
            token = Token(TT::RBRACE, "}");
            break;
        case '(':
            token = Token(TT::LPAREN, "(");
            break;
        case ')':
            token = Token(TT::RPAREN, ")");
            break;
        default:
            error();
        }

        advance();
        return token;
    }
    return Token(TT::END, "");
}

std::string Lexer::consume_while(const std::string& regex_string) {
    std::regex regex(regex_string);
    std::string res;

    while (std::regex_match(cur_char, regex)) {
        res += cur_char;
        advance();
    }
    return res;
}

void Lexer::ignore_spaces() {
    while (cur_char == " ")
        advance();
}

void Lexer::advance() {
    pos++;
    cur_char = pos > code.size() - 1 ? "<EOF>" : std::string(1, code[pos]);
}

void Lexer::error() {
    std::cout << "Current character: " << cur_char << "\nCurrent position: " << pos << "\n";
    throw std::invalid_argument("Syntax error!");
}
