#ifndef LEAFNODE_H
#define LEAFNODE_H

#include "Node.h"

class LeafNode : public Node {
    public:
        double getValue() const override;
        LeafNode(const int value_);
    private:
        double value;
};

LeafNode::LeafNode(const int value_) : value(value_) {}

double LeafNode::getValue() const {
    return value;
};

#endif