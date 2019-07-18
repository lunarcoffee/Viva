#include "gen.hh"

Generator::Generator(AST&& ast, std::ofstream& file) : ast(ast), file(file) {}

void Generator::gen() {
    auto root{ast.construct()};
    traverse(root);
}

void Generator::traverse(Node* node) {
//    if (!node->children.empty())
//        for (auto* n : node->children)
//            traverse(n);

    switch (node->type) {
        case NT::FUNC: {
            std::string raw_name{((FunctionDefinition*) node)->name};
            std::string name{raw_name == "main" ? "_start" : raw_name};
            file << "global " << name << "\n" << name << ":\n";
            traverse(node->children[0]);
            break;
        }
        case NT::RET:
            file << "mov eax, " << ((Return*) node)->constant.value << "\nret";
            break;
        default:
            throw std::invalid_argument("bruh");
    }
}
