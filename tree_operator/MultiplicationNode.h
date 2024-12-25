#ifndef MULTIPLICATION_NODE_H
#define MULTIPLICATION_NODE_H

#include "InnerNode.h"
#include "Node.h"

class MultiplicationNode : public InnerNode {
public:
    MultiplicationNode(Node* left_, Node* right_);
    double getValue() const override;
};

MultiplicationNode::MultiplicationNode(Node* left_, Node* right_) : InnerNode(left_, right_) {}

double MultiplicationNode::getValue() const {
    return left->getValue() * right->getValue();
};

#endif