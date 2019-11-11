#include <iostream>
#include "AVLTree.h"

int main() {
    AVLTree<int> avlTree;

    avlTree.insert(1);
    avlTree.insert(2);
    avlTree.insert(3);
    avlTree.insert(4);
    avlTree.insert(5);

    avlTree.preorder(avlTree.get_root());

    return 0;
}