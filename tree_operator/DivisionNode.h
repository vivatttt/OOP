#ifndef DIVISION_NODE_H
#define DIVISION_NODE_H

#include "InnerNode.h"

class DivisionNode : public InnerNode {
    public:
        DivisionNode(Node* left_, Node* right_);

        double getValue() const override;
};

DivisionNode::DivisionNode(Node* left_, Node* right_) : InnerNode(left_, right_) {}

double DivisionNode::getValue() const {
    return left->getValue() / right->getValue();
};

#endif