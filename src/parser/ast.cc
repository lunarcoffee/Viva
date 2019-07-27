#include <stdexcept>
#include <iostream>

#include "../lexer.hh"
#include "ast.hh"

AST::AST(Lexer&& lexer) : lexer(lexer) {}

std::shared_ptr<Node> AST::construct() {
    static auto root{program()};
    return root;
}

std::shared_ptr<Program> AST::program() {
    NRefVec funcs;
    auto func{function_definition()};
    while (func != nullptr) {
        funcs.emplace_back(func);
        func = function_definition();
    }
    return std::make_shared<Program>(std::move(funcs));
}

std::shared_ptr<FunctionDefinition> AST::function_definition() {
    auto return_type{lexer.next_token()};
    if (return_type.type == TT::END)
        return nullptr;
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

    auto return_value{exp()};
    semicolon();

    return std::make_shared<Return>(return_value);
}

std::shared_ptr<Expression> AST::exp() {
    auto peek_token{lexer.next_token()};
    lexer.send_back(peek_token);

    std::shared_ptr<Expression> value;
    if (peek_token.type == TT::ID)
        value = std::make_shared<Expression>(NRefVec{func_call()});
    else if (peek_token.type == TT::S32)
        value = std::make_shared<Expression>(NRefVec{constant()});
    else
        error();

    return value;
}

std::shared_ptr<FunctionCall> AST::func_call() {
    auto name{lexer.next_token()};
    if (name.type != TT::ID)
        error();

    auto lparen{lexer.next_token()};
    if (lparen.type != TT::LPAREN)
        error();

    auto rparen{lexer.next_token()};
    if (rparen.type != TT::RPAREN)
        error();

    return std::make_shared<FunctionCall>(std::move(name.value));
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
