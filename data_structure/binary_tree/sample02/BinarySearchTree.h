//
// Created by bong on 2023-03-20.
//

#ifndef SOCKETPROGRAM1_BINARYSEARCHTREE_H
#define SOCKETPROGRAM1_BINARYSEARCHTREE_H


class BinarySearchTree {
private:
    struct node {
        int data;

        node* left;
        node* right;
        node* parent;

    public:
        node():left(nullptr),right(nullptr),parent(nullptr),data(-1){};
    };

    node* root_;
    size_t size_;

    void releaseInner(node* t);
    node* findNode(int value);
    void printInnerTree(node *pNode);
    int deleteLeafNode(node *pNode);
    node *findRightest(node *pNode);
    node *findLeftest(node *pNode);
    int switchAndDelete(node *pNode, node *pNode1);
    bool isLeaf(node *pNode);

public:
    BinarySearchTree();
    ~BinarySearchTree() = default;

    void releaseTree();

    void printTree();

    int insertNode(int value);

    int deleteNode(int value);


};


#endif //SOCKETPROGRAM1_BINARYSEARCHTREE_H
