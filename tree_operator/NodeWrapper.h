#ifndef NODE_WRAPPER_H
#define NODE_WRAPPER_H

#include "Node.h"
#include "AdditionNode.h"
#include "SubtractionNode.h"
#include "MultiplicationNode.h"
#include "DivisionNode.h"

class NodeWrapper {
public:
    NodeWrapper(Node* node_) : node(node_) {}

    ~NodeWrapper();

    NodeWrapper operator+(const NodeWrapper& other) const;
    NodeWrapper operator-(const NodeWrapper& other) const;
    NodeWrapper operator*(const NodeWrapper& other) const;
    NodeWrapper operator/(const NodeWrapper& other) const;

    double getValue() const;

    private:
        Node* node;
};

NodeWrapper::~NodeWrapper() {
    delete node;
};
NodeWrapper NodeWrapper::operator+(const NodeWrapper& other) const {
    return NodeWrapper(new AdditionNode(this->node, other.node));
};

NodeWrapper NodeWrapper::operator-(const NodeWrapper& other) const {
    return NodeWrapper(new SubtractionNode(this->node, other.node));
};

NodeWrapper NodeWrapper::operator*(const NodeWrapper& other) const {
    return NodeWrapper(new MultiplicationNode(this->node, other.node));
};

NodeWrapper NodeWrapper::operator/(const NodeWrapper& other) const {
    return NodeWrapper(new DivisionNode(this->node, other.node));
};

double NodeWrapper::getValue() const {
    return node->getValue();
};

#endif