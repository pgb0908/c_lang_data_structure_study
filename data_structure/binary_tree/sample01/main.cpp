//
// Created by bong on 2023-02-17.
//

#include <iostream>

namespace bts01{
    typedef struct NODE {
        char szData[64];

        struct NODE* left;
        struct NODE* right;
        struct NODE* parent;
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

        printf("Left: [%p] | Cur: [%p], Data: %s Parent: %p | Right: [%p]\n",
               pParent->left,
               pParent, pParent->szData, pParent->parent,
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
            pNewNode->parent = nullptr;
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

    NODE* findNode(const char* pszData){
        NODE* pTmp = g_pRoot;

        while(pszData != pTmp->szData){
            if(strcmp(pTmp->szData, pszData) == 0){
                return pTmp;
            }else if(strcmp(pTmp->szData, pszData) > 0){
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

    int deleteNode(const char* pszData){
        // 1. 리프 노드이면 삭제
        // 2. 리프노드가 아니면
        //     - 삭제 노드 기준으로 왼쪽 --> 젤 오른쪽 느드가 삭제 노드 대신
        //          - 젤 오른쪽 노드에 왼쪽 자식 노드가 있으면 재귀적으로 대처
        //     - or, 삭제 노드 기준으로 오른쪽 --> 젤 왼쪽 노드가 삭제 노드 대신

        auto pDelete = findNode(pszData);
        if(pDelete == nullptr) return 0;

        if(pDelete->left == nullptr && pDelete->right == nullptr){
            // 리프 노드
            auto parent_pDel = pDelete->parent;

            if(parent_pDel->left->szData == pDelete->szData){
                parent_pDel->left = nullptr;
            }else{
                parent_pDel->right = nullptr;
            }
            free(pDelete);
            return 1;
        }

        if(pDelete->left != nullptr) {
            // 삭제할 노드의 왼쪽편이 존재!
            NODE *rightest = pDelete->left;

            // 왼쪽편 중에 가장 오른쪽!
            while (rightest->right != nullptr) {
                rightest = rightest->right;
            }

            // todo 1단계인지
            if(rightest->left == nullptr && rightest->right == nullptr){
                rightest->left = pDelete->left;
                rightest->right = pDelete->right;

                auto pre_rightest = rightest->parent;
                pre_rightest->right = nullptr;

                if(g_pRoot == pDelete){
                    g_pRoot = rightest;
                    rightest->parent = nullptr;
                }

                free(pDelete);
                return 1;
            }

            // todo 2단계인지
            if(rightest->parent->right == rightest){
                // 가장 오른쪽의 노드는 이진트리에서 오른쪽편
                //    - 이 노드를 삭제하려는 노드랑 체인지
                rightest->left = pDelete->left;
                rightest->right = pDelete->right;

                auto pre_rightest = rightest->parent;
                pre_rightest->right = nullptr;

                if(g_pRoot == pDelete){
                    g_pRoot = rightest;
                    rightest->parent = nullptr;
                }

                free(pDelete);

                return 1;
            }else{
                // 가장 오른쪽의 노드는 이진트리에서 왼쪽편
                //    - 삭제 노드의 왼쪽 편
                NODE* parent_pDelete = pDelete->parent;

                if(parent_pDelete != nullptr){
                    parent_pDelete->left = rightest;
                    rightest->parent = parent_pDelete;
                }else{
                    g_pRoot = rightest;
                    rightest->parent = nullptr;
                }
                rightest->right = pDelete->right;

                free(pDelete);

                return 1;
            }

        }else{
            // 삭제할 노드의 왼쪽편이 존재!
            NODE* leftest = pDelete->right;

            // 삭제 노드 오른쪽 중에 가장 왼쪽!
            while (leftest->left != nullptr) {
                leftest = leftest->left;
            }

            if(leftest->parent->left == leftest){
                // 가장 왼쪽의 노드는 이진트리에서 왼쪽편
                //    - 이 노드를 삭제하려는 노드랑 체인지
                leftest->left = pDelete->left;
                leftest->right = pDelete->right;

                auto pre_leftest = leftest->parent;
                pre_leftest->left = nullptr;

                if(g_pRoot == pDelete){
                    g_pRoot = leftest;
                    leftest->parent = nullptr;
                }

                free(pDelete);

                return 1;
            }else{
                // 가장 오른쪽의 노드는 이진트리에서 왼쪽편
                //    - 삭제 노드의 왼쪽 편
                NODE* parent_pDelete = pDelete->parent;

                if(parent_pDelete != nullptr){
                    parent_pDelete->right = leftest;
                    leftest->parent = parent_pDelete;
                }else{
                    g_pRoot = leftest;
                    leftest->parent = nullptr;
                }
                leftest->right = pDelete->right;

                free(pDelete);

                return 1;
            }

            return 0;
        }

    }

}

int main(){
    using namespace bts01;

    insertNode("5");
    insertNode("3");
    insertNode("7");
    insertNode("1");
    insertNode("4");
    insertNode("6");
    insertNode("9");

    printTree(g_pRoot);
    std::cout << "==========================" << std::endl;

    deleteNode("7");
    printTree(g_pRoot);

    //releaseTree(g_pRoot);
    //printTree(g_pRoot);

/*    auto node1 = findNode("5");
    if(node1 != nullptr){
        std::cout << "node1 find" << std::endl;
    }else{
        std::cout << "node1 not find" << std::endl;
    }

    auto node2 = findNode("6");
    if(node2 != nullptr){
        std::cout << "node2 find" << std::endl;
    }else{
        std::cout << "node2 not find" << std::endl;
    }*/

/*    auto node3 = findNode("8");
    if(node3 != nullptr){
        std::cout << "node3 find" << std::endl;
    }else{
        std::cout << "node3 not find" << std::endl;
    }*/


    return 0;
}