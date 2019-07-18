#include <string>

#include "token.hh"

Token::Token(): type(TT::END), value("") {}
Token::Token(TokenType type, std::string &&value) : type(type), value(value) {}
