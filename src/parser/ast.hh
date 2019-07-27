#ifndef AST_HH
#define AST_HH

#include "../lexer.hh"
#include "nodes.hh"

class AST {
public:
    explicit AST(Lexer&& lexer);
    std::shared_ptr<Node> construct();
private:
    Lexer lexer;

    std::shared_ptr<Program> program();
    std::shared_ptr<FunctionDefinition> function_definition();
    std::shared_ptr<Return> ret();
    std::shared_ptr<Expression> exp();
    std::shared_ptr<FunctionCall> func_call();
    std::shared_ptr<Constant> constant();

    void semicolon();
    static void error();
};

#endif
