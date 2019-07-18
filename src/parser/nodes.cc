#include <utility>

#include "nodes.hh"

Node::Node(NPtrVec&& children) : children(children) {}

FunctionDefinition::FunctionDefinition(
    std::string&& name,
    Return&& body) : Node(NPtrVec{std::make_shared<Return>(body)}), name(name), body(body) {}

Return::Return(int value)
    : constant(Constant{value}), Node(NPtrVec{std::make_shared<Constant>(this->constant)}) {}

Constant::Constant(int value) : Node(NPtrVec{}), value(value) {}
