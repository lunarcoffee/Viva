#include "nodes.hh"

Node::Node(NRefVec&& children, NT type) : children(children), type(type) {}

FunctionDefinition::FunctionDefinition(std::string&& name, Return&& body)
    : Node(NRefVec{&body}, NT::FUNC), name(name) {}

void FunctionDefinition::generate() {

}

Return::Return(int value) : constant(Constant{value}), Node(NRefVec{}, NT::RET) {}

void Return::generate() {

}

Constant::Constant(int value) : Node(NRefVec{}, NT::CONST), value(value) {}

void Constant::generate() {

}
