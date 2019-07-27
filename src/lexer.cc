#include <iostream>
#include <regex>
#include <stdexcept>

#include "lexer.hh"

Lexer::Lexer(std::string code) : code(code), pos(0), cur_char(std::string(1, code[0])) {}

Token Lexer::next_token() {
    // If there are values which have been sent back to the lexer (via [send_back] or other
    // internal means), finish sending those over lexing a new one from the code.
    if (!returned.empty()) {
        auto top{returned.top()};
        returned.pop();
        return top;
    }

    while (cur_char != "<EOF>") {
        ignore_spaces();

        // Try to consume an integer.
        if (isdigit(cur_char[0]))
            return Token(TT::S32, consume_while(R"(\d)"));

        // Try to consume a keyword. If it isn't a keyword, assume it is an identifier.
        if (isalpha(cur_char[0]) || cur_char == "_") {
            auto str{consume_while(R"(\w)")};
            return Token(str == "s32" || str == "return" ? TT::KEYWORD : TT::ID, std::move(str));
        }

        Token token;
        switch (cur_char[0]) {
        case ':':
            token = Token(TT::COLON, ":");
            break;
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

// Sends a token back to the lexer. This function is like the opposite of [next_token]. After
// calling this function, the next token that will be returned by [next_token] will be [token].
void Lexer::send_back(const Token& token) {
    returned.emplace(token);
}

std::string Lexer::consume_while(const std::string& regex_string) {
    std::regex regex{regex_string};
    std::string res;

    while (std::regex_match(cur_char, regex)) {
        res += cur_char;
        advance();
    }
    return res;
}

void Lexer::ignore_spaces() {
    while (cur_char == " " || cur_char == "\n")
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
