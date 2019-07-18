#ifndef NODES_HH
#define NODES_HH

#include <vector>
#include <string>
#include <memory>

class Node {
public:
    typedef std::vector<std::shared_ptr<Node>> NPtrVec;

    NPtrVec children;
protected:
    explicit Node(NPtrVec&& children);
};


class Constant : public Node {
public:
    int value;
    explicit Constant(int value);
};

class Return : public Node {
public:
    Constant constant;

    explicit Return(int value);
};

class FunctionDefinition : public Node {
public:
    std::string name;
    Return body;

    FunctionDefinition(std::string&& name, Return&& body);
};

#endif
