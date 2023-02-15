//
// Created by bong on 2023-02-15.
//

/// 구현 전 필요한 함수 목록 정의
/// initList() / releaseList()
/// printList()
/// findNode()
/// deleteNode()
/// insertAtHead() / insertAtTail()
/// getLength() = getSize()

#include <iostream>
#include <string>

namespace dll{

    typedef struct NODE {
        char pszData[64];

        struct NODE* prev;
        struct NODE* next;

    } NODE;

    NODE* g_pHead;
    NODE* g_pTail;
    int g_nSize;

    /**
     * 더미헤더와 더미테일 초기화 해준다
     */
    void initList(){
        g_pHead = (NODE*) malloc(sizeof(NODE));
        g_pTail = (NODE*) malloc(sizeof(NODE));
        g_nSize = 0;

        memset(g_pHead, 0, sizeof(NODE));
        memset(g_pTail, 0, sizeof(NODE));
        strcpy_s(g_pHead->pszData, sizeof(g_pHead->pszData), "Head");
        strcpy_s(g_pTail->pszData, sizeof(g_pTail->pszData), "Tail");

        g_pHead->next = g_pTail;
        g_pTail->prev = g_pHead;
    }


    void releaseList(){
        NODE* pTmp = g_pHead->next;

        while(pTmp != g_pTail){
            NODE* pDelete = pTmp; // back up!!
            pTmp = pTmp->next;

            printf("free [%p], data: %s \n", pDelete, pDelete->pszData);
            free(pDelete);
        }
        std::cout << std::endl;

        g_pHead->next = g_pTail;
        g_pTail->prev = g_pHead;
        g_nSize = 0;
    }

    void printList(){
        NODE* pTmp = g_pHead;

        printf("PrintList(): g_nSize: %d, g_pHead [%p], g_pTail [%p]\n", g_nSize, g_pHead, g_pTail);
        while(pTmp != nullptr){
            printf("Prev: [%p] | Cur: [%p], Data: %s | Next: [%p]\n", pTmp->prev, pTmp, pTmp->pszData, pTmp->next);
            pTmp = pTmp->next;
        }
        std::cout << std::endl;
    }

    NODE* findNode(const char* pszData){
        NODE* pTmp = g_pHead->next;

        while (pTmp != g_pTail){
            if(strcmp(pTmp->pszData, pszData)==0)
                return pTmp;
            pTmp = pTmp->next;
        }

        return nullptr;
    }

    void insertBefore(NODE *pNode, const char *data) {

        NODE* pNewNode = (NODE*) malloc(sizeof(NODE));
        memset(pNewNode, 0, sizeof(NODE));
        strcpy_s(pNewNode->pszData, sizeof(pNewNode->pszData), data);

        pNewNode->prev = pNode->prev;
        pNewNode->next = pNode;

        pNode->prev = pNewNode;
        pNewNode->prev->next = pNewNode;

        g_nSize++;
    }

    int deleteNode(const char* pszData){
        NODE* pNode = findNode(pszData);

        pNode->prev->next = pNode->next;
        pNode->next->prev = pNode->prev;

        printf("deleteNode: [%p], data: %s \n", pNode, pNode->pszData);
        free(pNode);

        g_nSize--;

        return 0;
    }

    int insertAtHead(const char* pszData){

        NODE* pNewNode = (NODE*) malloc(sizeof(NODE));
        memset(pNewNode, 0, sizeof(NODE));
        strcpy_s(pNewNode->pszData, sizeof(pNewNode->pszData), pszData);

        pNewNode->next = g_pHead->next;
        pNewNode->prev = g_pHead;

        g_pHead->next = pNewNode;
        pNewNode->next->prev = pNewNode;

        g_nSize++;

        return g_nSize;
    }

    int insertAtTail(const char* pszData){
        insertBefore(g_pTail, pszData);
        return g_nSize;
    }

    int getSize(){
        return g_nSize;
    }

    int getLength(){
        return getSize();
    }

    bool isEmpty(){
        return getSize() == 0;
    }


    int insertAt(int idx, const char* pszData){
        int i = 0;
        NODE* pTmp = g_pHead->next;
        while(pTmp != g_pTail){

            if(i == idx){
                insertBefore(pTmp, pszData);
                return i;
            }

            pTmp = pTmp->next;
            i++;
        }
        insertAtTail(pszData);

        return i;
    }


    NODE* getAt(int idx){
        int i = 0;
        NODE* pTmp = g_pHead->next;

        while(pTmp != g_pTail){
            if(i == idx)
                return pTmp;

            pTmp = pTmp->next;
            i++;
        }

        return nullptr;
    }

}

int main(){
    using namespace dll;
    initList();
    printList();

    insertAtTail("TEST01");
    insertAtTail("TEST02");
    insertAtTail("TEST03");
    //insertAtHead("TEST03");
    printList();

    insertAt(0, "TEST AT 00");
    printList();

    insertAt(2, "TEST AT 02");
    printList();

    insertAt(4, "TEST AT 04");
    printList();

    insertAt(10, "TEST AT 10");
    printList();

    releaseList();
    printList();

    return 0;
}