//
// Created by Святослав on 10.03.2024.
//

#include <iostream>
#include "Tree.h"
#include <set>

int main() {
    Tree<int> bst;
    Tree<int>::value_type g;
//    static_assert(std::is_same<int, Tree<int>::value_type>());
    bst.insert(100);
    bst.insert(50);
    bst.insert(1);
    bst.insert(5);
    bst.insert(1300);
    Tree<int>::InIterator i = bst.end<InOrder>();
    i--;
    std::cout << *i << "\n";
    for (Tree<int>::InIterator i = bst.begin<InOrder>(); i != bst.end<InOrder>(); i++) {
        std::cout << *i << " ";
        
    }
    
}