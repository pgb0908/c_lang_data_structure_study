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

    int deleteLeafNode(NODE *pNode);
    bool isLeaf(NODE *pNode);

    NODE *findRightest(NODE *pNode);

    int switchAndDelete(NODE *pNODE, NODE* pDelete);

    NODE *findLeftest(NODE *pNode);

    int deleteNode(const char* pszData){
        auto pDelete = findNode(pszData);
        if(pDelete == nullptr) return 0;

        if(pDelete->left == nullptr && pDelete->right == nullptr){
            // 리프 노드
            deleteLeafNode(pDelete);
            return 1;
        }else if(pDelete->left != nullptr && pDelete->right == nullptr){
            // 리프노드가 아니고 왼쪽 노드만 있는경우
            // 왼쪽편 가장 오른쪽에 있는 놈을 삭제할 놈을 대체

            // 가장 오른쪽 검색!
            NODE* pRightest = findRightest(pDelete);
            int rtn = switchAndDelete(pRightest, pDelete);

            return rtn;

        }else if(pDelete->left == nullptr && pDelete->right != nullptr){
            // 리프노드가 아니고 오른쪽 노드만 있는경우
            // 오른편 가장 왼쪽에 있는 놈을 삭제할 놈을 대체

            NODE* pLeftest = findLeftest(pDelete);
            int rtn = switchAndDelete(pLeftest, pDelete);

            return rtn;
        }else{
            NODE* pRightest = findRightest(pDelete);
            int rtn = switchAndDelete(pRightest, pDelete);

            return rtn;
        }

    }

    NODE *findLeftest(NODE *pNode) {
        NODE* pTemp = pNode->right;

        while(!isLeaf(pTemp)){
            if(pTemp->left != nullptr){
                pTemp = pTemp->left;
                continue;
            }

            if(pTemp->right != nullptr)
                pTemp = pTemp->right;
        }

        if(pTemp != pNode->right){
            return  pTemp;
        }else{
            return pNode->right;
        }
    }

    NODE *findRightest(NODE *pNode) {
        NODE* pTemp = pNode->left;

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

    int switchAndDelete(NODE *pNode, NODE* pDelete) {
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
        pNode->right = pDelete->right;
        pNode->left = pDelete->left;

        free(pDelete);
        return 0;
    }


    bool isLeaf(NODE *pNode) {
        if(pNode == nullptr) return false;

        if(pNode->right == nullptr &&
           pNode->left == nullptr) return true;

        return false;
    }

    int deleteLeafNode(NODE *pDelete) {
        auto parent_pDel = pDelete->parent;

        if(parent_pDel->left->szData == pDelete->szData){
            parent_pDel->left = nullptr;
        }else{
            parent_pDel->right = nullptr;
        }
        free(pDelete);

        return 1;
    }

}

int main(){
    using namespace bts01;

/*    insertNode("5");
    insertNode("3");
    insertNode("7");
    insertNode("1");
    insertNode("4");
    insertNode("6");
    insertNode("9");*/

    insertNode("");


    printTree(g_pRoot);
    std::cout << "==========================" << std::endl;

    deleteNode("1");
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