//
// Created by Святослав on 10.03.2024.
//

#include <iostream>
#include "Tree.h"

int main() {
    while (true) {
        Tree<int> bst;
        Tree<int> bst2;
        bst.insert(1);
        bst.insert(2);
        bst.insert(3);
        bst2.insert(1000);
        bst.merge(bst2);
    }
}