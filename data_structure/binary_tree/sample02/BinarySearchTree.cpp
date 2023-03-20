//
// Created by bong on 2023-03-20.
//

#include <iostream>
#include "BinarySearchTree.h"
#include "format"

BinarySearchTree::BinarySearchTree():size_(0), root_(nullptr) {

}


void BinarySearchTree::releaseTree() {
    releaseInner(root_);
    root_ = nullptr;
}

void BinarySearchTree::printTree() {
    std::cout << "========= start print ===========" << std::endl;
    printInnerTree(root_);
    std::cout << "========== end print ============" << std::endl << std::endl;
}

int BinarySearchTree::insertNode(int value) {
    node* pNewNode = new node;
    pNewNode->data = value;

    if(root_ == nullptr){
        // 기존에 노드가 존재하지 않으면
        // 루트는 새로운 노드가 됨
        pNewNode->parent = nullptr;
        root_ = pNewNode;
        return 1;
    }

    // 루트 노드와 비교
    auto pTmp = root_;

    while(pTmp != nullptr){
        if(pTmp->data > value){
            // left
            if(pTmp->left == nullptr){
                pTmp->left = pNewNode;
                pNewNode->parent = pTmp;
                break;
            }else{
                pTmp = pTmp->left;
                continue;
            }
        }else{
            // right
            if(pTmp->right == nullptr){
                pTmp->right = pNewNode;
                pNewNode->parent = pTmp;
                break;
            }else{
                pTmp = pTmp->right;
                continue;
            }
        }
    }

    return 0;
}

BinarySearchTree::node *BinarySearchTree::findNode(int value) {
    node* pTmp = root_;

    while(value != pTmp->data){
        if(pTmp->data == value){
            return pTmp;
        }else if(pTmp->data > value){
            // left
            if(pTmp->left != nullptr){
                pTmp = pTmp->left;
            }else{
                return nullptr;
            }
        }else{
            // right
            if(pTmp->right != nullptr){
                pTmp = pTmp->right;
            }else{
                return nullptr;
            }
        }
    }

    return pTmp;
}

void BinarySearchTree::releaseInner(node* target) {
    if(target == nullptr) return;

    releaseInner(target->left);
    releaseInner(target->right);

    delete target;
}

void BinarySearchTree::printInnerTree(BinarySearchTree::node *target) {
    if(target == nullptr) return;

    printInnerTree(target->left);

    //data: {} | Left[{}] Cur[{}] Right[{}]
    printf("Data: %d | Left: [%p] Cur: [%p] Right: [%p] | parent: [%p]\n",
           target->data,
           target->left,
           target,
           target->right,
           target->parent);

    //std::format("Cur:{:#010x}",  reinterpret_cast<intptr_t>(target));
    printInnerTree(target->right);
}

int BinarySearchTree::deleteNode(int value) {
    auto pDelete = findNode(value);
    if(pDelete == nullptr) return 0;

    if(pDelete->left == nullptr && pDelete->right == nullptr){
        // 리프 노드
        int rtn = deleteLeafNode(pDelete);
        return rtn;
    }else if(pDelete->left != nullptr && pDelete->right == nullptr){
        // 리프노드가 아니고 왼쪽 노드만 있는경우
        // 왼쪽편 가장 오른쪽에 있는 놈을 삭제할 놈을 대체

        // 가장 오른쪽 검색!
        node* pRightest = findRightest(pDelete);
        int rtn = switchAndDelete(pRightest, pDelete);

        return rtn;

    }else if(pDelete->left == nullptr && pDelete->right != nullptr){
        // 리프노드가 아니고 오른쪽 노드만 있는경우
        // 오른편 가장 왼쪽에 있는 놈을 삭제할 놈을 대체

        node* pLeftest = findLeftest(pDelete);
        int rtn = switchAndDelete(pLeftest, pDelete);

        return rtn;
    }else{
        node* pRightest = findRightest(pDelete);
        int rtn = switchAndDelete(pRightest, pDelete);

        return rtn;
    }
}

int BinarySearchTree::deleteLeafNode(BinarySearchTree::node *pNode) {
    auto parent_pDel = pNode->parent;

    if(parent_pDel->left->data == pNode->data){
        parent_pDel->left = nullptr;
    }else{
        parent_pDel->right = nullptr;
    }

    delete pNode;

    return 1;
}

BinarySearchTree::node *BinarySearchTree::findRightest(BinarySearchTree::node *pNode) {
    node* pTemp = pNode->left;

    while(!isLeaf(pTemp)){
        if(pTemp->right != nullptr){
            pTemp = pTemp->right;
            continue;
        }

        if(pTemp->left != nullptr)
            pTemp = pTemp->left;
    }

    if(pTemp != pNode->left){
        return  pTemp;
    }else{
        return pNode->left;
    }
}

BinarySearchTree::node *BinarySearchTree::findLeftest(BinarySearchTree::node *pNode) {
    node* pTemp = pNode->right;

    while(!isLeaf(pTemp)){
        if(pTemp->left != nullptr){
            pTemp = pTemp->left;
            continue;
        }

        if(pTemp->right != nullptr)
            pTemp = pTemp->right;
    }

    if(pTemp->data > pNode->right->data){
        return pNode->right;
    }else{
        return pTemp;
    }

}

int BinarySearchTree::switchAndDelete(BinarySearchTree::node *pNode, BinarySearchTree::node *pDelete) {
    // 대상 노드의 부모 노드 관계 삭제
    auto pNodeParent = pNode->parent;
    if(pNodeParent->left == pNode){
        // left
        pNodeParent->left = nullptr;
    }else{
        // right
        pNodeParent->right = nullptr;
    }

    // 삭제 노드의 부모 노드와 부모관계
    auto pDelParent = pDelete->parent;
    if(pDelParent == nullptr){
        std::cout << "todo" << std::endl;
    }else if(pDelParent->left == pDelete){
        // left
        pDelParent->left = pNode;
    }else{
        // right
        pDelParent->right = pNode;
    }
    pNode->parent = pDelParent;


    // 기존 노드와 삭제노드 부모관계
    if(pNode->right == nullptr)
        pNode->right = pDelete->right;

    if(pNode->left == nullptr)
        pNode->left = pDelete->left;

    if(pDelete->right != nullptr){
        pDelete->right->parent = pNode;
    }
    if(pDelete->left != nullptr){
        pDelete->left->parent = pNode;
    }


    delete pDelete;
    return 0;
}

bool BinarySearchTree::isLeaf(BinarySearchTree::node *pNode) {
    if(pNode == nullptr) return false;

    if(pNode->right == nullptr &&
       pNode->left == nullptr) return true;

    return false;
}

