#ifndef NODES_HH
#define NODES_HH

#include <vector>
#include <string>
#include <memory>
#include <variant>

enum class NodeType {
    PROGRAM, FUNC, RET, EXP, FUNC_CALL, CONST
};

typedef NodeType NT;

class Node {
public:
    NT type;
    std::vector<std::shared_ptr<Node>> children;
protected:
    Node(std::vector<std::shared_ptr<Node>>&& children, NT type);
};

typedef std::vector<std::shared_ptr<Node>> NRefVec;

class Constant : public Node {
public:
    int value;
    explicit Constant(int value);
};

class FunctionCall : public Node {
public:
    std::string name;
    explicit FunctionCall(std::string&& name);
};

class Expression : public Node {
public:
    explicit Expression(NRefVec&& children);
};

class Return : public Node {
public:
    explicit Return(const std::shared_ptr<Expression>& value);
};

class FunctionDefinition : public Node {
public:
    std::string name;
    FunctionDefinition(std::string&& name, const std::shared_ptr<Return>& body);
};

class Program : public Node {
public:
    explicit Program(NRefVec&& children);
};

#endif
