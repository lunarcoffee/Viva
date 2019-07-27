#ifndef NODES_HH
#define NODES_HH

#include <vector>
#include <string>
#include <memory>
#include <variant>

enum class NodeType {
    FUNC, RET, CONST
};
typedef NodeType NT;

class Node {
public:
    NT type;
    typedef std::vector<std::shared_ptr<Node>> NRefVec;
    NRefVec children;
protected:
    Node(NRefVec&& children, NT type);
};

class Constant : public Node {
public:
    int value;
    explicit Constant(int value);
};

class Return : public Node {
public:
    std::shared_ptr<Constant> constant;
    explicit Return(std::shared_ptr<Constant> value);
};

class FunctionDefinition : public Node {
public:
    std::string name;
    FunctionDefinition(std::string&& name, const std::shared_ptr<Return>& body);
};

#endif
