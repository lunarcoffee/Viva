#include <stdexcept>
#include <iostream>

#include "../lexer.hh"
#include "ast.hh"

AST::AST(Lexer&& lexer) : lexer(lexer) {}

void AST::construct() {
    auto main{function_definition()};
}

FunctionDefinition AST::function_definition() {
    auto return_type{lexer.next_token()};
    if (return_type.type != TT::KEYWORD || return_type.value != "int")
        error();

    auto name{lexer.next_token()};
    if (name.type != TT::ID)
        error();

    auto lparen{lexer.next_token()};
    auto rparen{lexer.next_token()};
    if (lparen.type != TT::LPAREN || rparen.type != TT::RPAREN)
        error();

    auto lbrace{lexer.next_token()};
    if (lbrace.type != TT::LBRACE)
        error();

    auto return_stmt{ret()};

    auto rbrace{lexer.next_token()};
    if (rbrace.type != TT::RBRACE)
        error();

    return FunctionDefinition(std::move(name.value), std::move(return_stmt));
}

Return AST::ret() {
    auto return_stmt{lexer.next_token()};
    if (return_stmt.type != TT::KEYWORD || return_stmt.value != "return")
        error();

    auto return_value{constant()};
    semicolon();

    return Return(return_value.value);
}

Constant AST::constant() {
    auto return_value{lexer.next_token()};
    if (return_value.type != TT::INT)
        error();
    return Constant(std::stoi(return_value.value));
}

void AST::semicolon() {
    auto semicolon{lexer.next_token()};
    if (semicolon.type != TT::SEMICOLON)
        error();
}

void AST::error() {
    throw std::invalid_argument("Invalid syntax!");
}
