//
// Created by bong on 2023-03-20.
//

#include <iostream>
#include "BinarySearchTree.h"

int main() {
    BinarySearchTree myBst;

/*    myBst.insertNode(5);
    myBst.insertNode(1);
    myBst.insertNode(3);
    myBst.insertNode(6);
    myBst.insertNode(7);
    myBst.insertNode(4);
    myBst.insertNode(9);*/

/*    myBst.insertNode(5);
    myBst.insertNode(3);
    myBst.insertNode(7);
    myBst.insertNode(1);
    myBst.insertNode(4);
    myBst.insertNode(6);
    myBst.insertNode(9);*/

/*    myBst.insertNode(5);
    myBst.insertNode(3);
    myBst.insertNode(10);
    myBst.insertNode(1);
    myBst.insertNode(0);
    myBst.insertNode(2);*/

    myBst.insertNode(5);
    myBst.insertNode(3);
    myBst.insertNode(10);
    myBst.insertNode(13);
    myBst.insertNode(11);
    myBst.insertNode(15);

    myBst.printTree();

    myBst.deleteNode(10);

    myBst.printTree();

    return 0;
}