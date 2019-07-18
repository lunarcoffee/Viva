#ifndef NODES_HH
#define NODES_HH

#include <vector>
#include <string>
#include <memory>

enum class NodeType {
    FUNC, RET, CONST
};
typedef NodeType NT;

class Node {
public:
    NT type;
    typedef std::vector<Node*> NRefVec;
    NRefVec children;

    virtual void generate() = 0;
protected:
    explicit Node(NRefVec&& children, NT type);
};


class Constant : public Node {
public:
    int value;

    explicit Constant(int value);
    void generate() override;
};

class Return : public Node {
public:
    Constant constant;

    explicit Return(int value);
    void generate() override;
};

class FunctionDefinition : public Node {
public:
    std::string name;

    FunctionDefinition(std::string&& name, Return&& body);
    void generate() override;
};

#endif
