#include <utility>

#include <iostream>
#include "nodes.hh"

Node::Node(NRefVec&& children, NT type) : children(children), type(type) {}

FunctionDefinition::FunctionDefinition(std::string&& name, const std::shared_ptr<Return>& body)
    : Node(NRefVec{body}, NT::FUNC), name(name) {}

Return::Return(std::shared_ptr<Constant> value)
    : constant(std::move(value)), Node(NRefVec{}, NT::RET) {}

Constant::Constant(int value) : Node(NRefVec{}, NT::CONST), value(value) {}
