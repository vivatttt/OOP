#ifndef NODE_H
#define NODE_H
#include <iostream>

class Node  {
    public:
        virtual double getValue() const = 0;
        friend std::ostream& operator<<(std::ostream& os, Node* leaf) {
            os << "Node value is " << leaf->getValue() << std::endl;
            return os;
        }
};

#endif