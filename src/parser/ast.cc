#include <stdexcept>
#include <iostream>

#include "../lexer.hh"
#include "ast.hh"

AST::AST(Lexer&& lexer) : lexer(lexer) {}

std::shared_ptr<Node> AST::construct() {
    static auto root{function_definition()};
    return root;
}

std::shared_ptr<FunctionDefinition> AST::function_definition() {
    auto return_type{lexer.next_token()};
    if (return_type.type != TT::KEYWORD || return_type.value != "s32")
        error();

    auto name{lexer.next_token()};
    if (name.type != TT::ID)
        error();

    auto colon{lexer.next_token()};
    if (colon.type != TT::COLON)
        error();

    auto lbrace{lexer.next_token()};
    if (lbrace.type != TT::LBRACE)
        error();

    auto return_stmt{ret()};

    auto rbrace{lexer.next_token()};
    if (rbrace.type != TT::RBRACE)
        error();

    return std::make_shared<FunctionDefinition>(std::move(name.value), return_stmt);
}

std::shared_ptr<Return> AST::ret() {
    auto return_stmt{lexer.next_token()};
    if (return_stmt.type != TT::KEYWORD || return_stmt.value != "return")
        error();

    auto return_value{constant()};
    semicolon();

    return std::make_shared<Return>(return_value);
}

std::shared_ptr<Constant> AST::constant() {
    auto return_value{lexer.next_token()};
    if (return_value.type != TT::S32)
        error();
    return std::make_shared<Constant>(std::stoi(return_value.value));
}

void AST::semicolon() {
    auto semicolon{lexer.next_token()};
    if (semicolon.type != TT::SEMICOLON)
        error();
}

void AST::error() {
    throw std::invalid_argument("Invalid syntax!");
}
