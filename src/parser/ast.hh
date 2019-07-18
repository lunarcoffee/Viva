#ifndef AST_HH
#define AST_HH

#include "../lexer.hh"
#include "nodes.hh"

class AST {
public:
    explicit AST(Lexer&& lexer);
    void construct();
private:
    Lexer lexer;

    FunctionDefinition function_definition();
    Return ret();
    Constant constant();

    void semicolon();
    static void error();
};

#endif
