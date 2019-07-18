#include <stdexcept>
#include <iostream>

#include "../lexer.hh"
#include "ast.hh"

AST::AST(Lexer&& lexer) : lexer(lexer) {}

void AST::construct() {
    FunctionDefinition main{function_definition()};
    std::cout << main.name << main.body.constant.value;
}

FunctionDefinition AST::function_definition() {
    Token return_type{lexer.next_token()};
    if (return_type.type != TT::KEYWORD || return_type.value != "int")
        error();

    Token name{lexer.next_token()};
    if (name.type != TT::ID)
        error();

    Token lparen{lexer.next_token()};
    Token rparen{lexer.next_token()};
    if (lparen.type != TT::LPAREN || rparen.type != TT::RPAREN)
        error();

    Token lbrace{lexer.next_token()};
    if (lbrace.type != TT::LBRACE)
        error();

    Return return_stmt{ret()};

    Token rbrace{lexer.next_token()};
    if (rbrace.type != TT::RBRACE)
        error();

    return FunctionDefinition(std::move(name.value), std::move(return_stmt));
}

Return AST::ret() {
    Token return_stmt{lexer.next_token()};
    if (return_stmt.type != TT::KEYWORD || return_stmt.value != "return")
        error();

    Token return_value{lexer.next_token()};
    if (return_value.type != TT::INT)
        error();

    semicolon();
    return Return(std::stoi(return_value.value));
}

Constant AST::constant() {

}

void AST::semicolon() {
    Token semicolon{lexer.next_token()};
    if (semicolon.type != TT::SEMICOLON)
        error();
}

void AST::error() {
    throw std::invalid_argument("Invalid syntax!");
}
