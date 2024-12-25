#ifndef ADDITION_NODE_H
#define ADDITION_NODE_H

#include "InnerNode.h"

class AdditionNode : public InnerNode {
    public:
        AdditionNode(Node* left_, Node* right_);

        double getValue() const override;
};

AdditionNode::AdditionNode(Node* left_, Node* right_) : InnerNode(left_, right_) {}

double AdditionNode::getValue() const {
    return left->getValue() + right->getValue();
};

#endif