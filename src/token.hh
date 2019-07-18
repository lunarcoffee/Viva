#ifndef TOKEN_HH
#define TOKEN_HH

#include <string>

enum class TokenType {
    INT, ID, KEYWORD, SEMICOLON, LBRACE, RBRACE, LPAREN, RPAREN, END
};
typedef TokenType TT;

class Token {
public:
    TokenType type;
    std::string value;

    Token();
    Token(TokenType type, std::string&& value);
};

#endif
