#include "gen.hh"

Generator::Generator(AST&& ast, std::ofstream& file) : ast(ast), file(file) {}

void Generator::gen() {
    traverse(ast.construct());
}

void Generator::traverse(const std::shared_ptr<Node>& node) {
    switch (node->type) {
    case NT::FUNC: {
        std::string raw_name{reinterpret_cast<FunctionDefinition*>(node.get())->name};
        std::string name{raw_name == "main" ? "_start" : raw_name};
        file << "global " << name << "\n" << name << ":\n";
        traverse(node->children[0]);
        break;
    }
    case NT::RET: {
        auto r{reinterpret_cast<Return*>(node.get())};
//        file << "mov eax, " << r->exp-> << "\nret";
        break;
    }
    default:
        throw std::invalid_argument("AST is incorrect!");
    }
}
