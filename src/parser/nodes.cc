#include <utility>

#include <iostream>
#include "nodes.hh"

Node::Node(NRefVec&& children, NT type) : children(children), type(type) {}

Program::Program(NRefVec&& children) : Node(std::move(children), NT::PROGRAM) {}

FunctionDefinition::FunctionDefinition(std::string&& name, const std::shared_ptr<Return>& body)
    : Node(NRefVec{body}, NT::FUNC), name(name) {}

Return::Return(const std::shared_ptr<Expression>& value) : Node(NRefVec{value}, NT::RET) {}

Expression::Expression(NRefVec&& children) : Node(std::move(children), NT::EXP) {}

FunctionCall::FunctionCall(std::string&& name) : Node(NRefVec{}, NT::FUNC_CALL), name(name) {}

Constant::Constant(int value) : Node(NRefVec{}, NT::CONST), value(value) {}
