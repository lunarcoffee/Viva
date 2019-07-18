#ifndef GEN_HH
#define GEN_HH

#include <fstream>

#include "parser/ast.hh"

class Generator {
public:
    Generator(AST&& ast, std::ofstream& file);
    void gen();
private:
    AST ast;
    std::ofstream& file;

    void traverse(Node* node);
};

#endif
