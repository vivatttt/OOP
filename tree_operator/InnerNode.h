#ifndef INNERNODE_H
#define INNERNODE_H

#include "Node.h"

class InnerNode : public Node {
    public:
        InnerNode(Node* left_, Node* right_);
        // ~InnerNode() override;
    protected:
        Node* left;
        Node* right; 
};

InnerNode::InnerNode(Node* left_, Node* right_) : left(left_), right(right_) {}

// InnerNode::~InnerNode() {
//     delete left;
//     delete right;
// };

#endif