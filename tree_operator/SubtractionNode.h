#ifndef SUBTRACTION_NODE_H
#define SUBTRACTION_NODE_H

#include "InnerNode.h"

class SubtractionNode : public InnerNode {
public:
    SubtractionNode(Node* left_, Node* right_);

    double getValue() const override;
};

SubtractionNode::SubtractionNode(Node* left_, Node* right_) : InnerNode(left_, right_) {}

double SubtractionNode::getValue() const {
    return left->getValue() - right->getValue();
};

#endif