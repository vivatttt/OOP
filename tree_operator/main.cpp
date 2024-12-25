#include <iostream>

#include "LeafNode.h"
#include "NodeWrapper.h"
#include "AdditionNode.h"
#include "SubtractionNode.h"
#include "MultiplicationNode.h"
#include "DivisionNode.h"

int main(){
    // в NodeWrapper.h приведены безуспешные старания реализовать перегрузку операторов 
    // через обертку над узлом дерева
    // в силу того, что они безуспешные, тесты приведены в лоб через создание вложенных объектов
    
    // для запуска:
    // make clean && make run
    Node* leaf = new LeafNode(12.0);
    Node* LeftSubTree = new SubtractionNode(new DivisionNode(leaf, new LeafNode(2.0)), new MultiplicationNode(new LeafNode(2.0), new LeafNode(1.0))); 
    Node* RightSubTree = new MultiplicationNode(new LeafNode(10.0), new LeafNode(2.0));
    Node* Tree = new AdditionNode(LeftSubTree, RightSubTree);

    /*
                Tree
                  +
    LeftSubTree /    \ RightSubTree 
               -       *
             /   \    / \
            :     *  10  2
           / \   / \
         12   2 2   1
    */
   
    std::cout << "Leaf" << leaf;
    std::cout << "Evaluated LeftSubTree" << LeftSubTree;
    std::cout << "Evaluated RightSubTree"<< RightSubTree;
    std::cout << "Evaluated Tree"<< Tree;

    return 0;
}
