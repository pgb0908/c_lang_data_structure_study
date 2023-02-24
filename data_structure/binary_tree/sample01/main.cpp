//
// Created by bong on 2023-02-17.
//

#include <iostream>

namespace bts01{
    typedef struct NODE {
        char szData[64];

        struct NODE* left;
        struct NODE* right;
    } NODE;

    NODE* g_pRoot;
    int g_nSize;

    void releaseTree(NODE* pParent){
        if(pParent == nullptr) return;

        releaseTree(pParent->left);
        releaseTree(pParent->right);

        free(pParent);
        g_pRoot = nullptr;
    }

    void printTree(NODE* pParent){
        if(pParent == nullptr) return;

        printTree(pParent->left);

        printf("Left: [%p] | Cur: [%p], Data: %s | Right: [%p]\n",
               pParent->left,
               pParent, pParent->szData,
               pParent->right);

        printTree(pParent->right);

        return;

    }

    int insertNode(const char* pszData){
        NODE* pNewNode = (NODE*) malloc(sizeof(NODE));
        memset(pNewNode, 0, sizeof(NODE));
        strcpy_s(pNewNode->szData, sizeof(pNewNode->szData), pszData);

        if(g_pRoot == nullptr){
            // 기존에 노드가 존재하지 않으면
            // 루트는 새로운 노드가 됨
            g_pRoot = pNewNode;
            return 1;
        }

        // 루트 노드와 비교
        NODE* pTmp = g_pRoot;

        while(pTmp != nullptr){
            if(strcmp(pTmp->szData, pszData) > 0){
                // left
                if(pTmp->left == nullptr){
                    pTmp->left = pNewNode;
                    break;
                }else{
                    pTmp = pTmp->left;
                    continue;
                }
            }else{
                // right
                if(pTmp->right == nullptr){
                    pTmp->right = pNewNode;
                    break;
                }else{
                    pTmp = pTmp->right;
                    continue;
                }
            }
        }

        return 0;
    }

    NODE* findNode(const char* pszData){

        return nullptr;
    }

    int deleteNode(const char* pszData){

        return 0;
    }

}

int main(){
    using namespace bts01;

    insertNode("5");
    insertNode("4");
    insertNode("7");
    insertNode("8");

    printTree(g_pRoot);

    releaseTree(g_pRoot);
    printTree(g_pRoot);

    return 0;
}