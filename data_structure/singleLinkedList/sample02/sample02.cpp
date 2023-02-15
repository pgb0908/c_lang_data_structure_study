//
// Created by bong on 2023-02-13.
//

#include <iostream>

namespace sample02 {

    typedef struct NODE {
        char szData[64];

        struct NODE *next;
    } NODE;

    NODE *g_pHead = nullptr;

    /**
     * 연결 리스트 전체 데이터 출력
     */
    void printList() {
        NODE *pHead = g_pHead;
        while (pHead != nullptr) {
            // 구조체 string에서 문자 깨짐 발생. 왜???
            //std::cout << g_pHead << "  " << g_pHead->szData.c_str() << "  " << g_pHead->next << std::endl;
            printf("[%p] : %s , next[%p] \n", pHead, pHead->szData, pHead->next);

            pHead = pHead->next;
        }
        putchar('\n');
    }

    int insertNewNode(const char *strData) {
        NODE *pNode = (NODE *) malloc(sizeof(NODE));
        memset(pNode, 0, sizeof(NODE));
        //pNode->szData = strData;
        strcpy_s(pNode->szData, sizeof(pNode->szData), strData);

        if (g_pHead == nullptr) {
            g_pHead = pNode;
        } else {
            // head --> new_node --> old_node
            // 1. new_node가 old_node 가리킴
            // 2. head는 new_node가 됨

            pNode->next = g_pHead;
            g_pHead = pNode;
        }

        return 1;
    }

    void releaseList(void){
        NODE *pTemp = g_pHead;

        while(pTemp != nullptr){
            NODE *pDelete = pTemp;
            pTemp = pTemp->next;

            printf("Delete: [%p] %s\n", pDelete, pDelete->szData);
            free(pDelete);
        }

        g_pHead->next = nullptr;

    }

    NODE *findData(char* pszData){
        NODE *pCur = g_pHead->next;
        NODE *pPrev = g_pHead;

        while(pCur != nullptr){
            if(strcmp(pszData, pCur->szData) == 0){
                return pPrev;
            }
            pPrev = pPrev->next;
            pCur = pCur->next;
        }

        return 0;
    }

    int deleteData(char* pszData){

        NODE *pTemp = g_pHead;
        NODE *pPrev = nullptr;

        while(pTemp != nullptr){
            if(strcmp(pszData, pTemp->szData) == 0){

                printf("Delete: [%p] %s\n", pTemp, pTemp->szData);
                if (pPrev != nullptr) {
                    pPrev->next = pTemp->next;
                } else {
                    g_pHead = pTemp->next;
                }
                free(pTemp);

                return 1;
            }

            pPrev = pTemp; // 현재 포지션이 prev가 됨
            pTemp = pTemp->next; // 다음 노드로 넘어감
        }

        return 0;
    }


}

int main() {
    using namespace sample02;

    // List 테스트를 위한 코드
    insertNewNode("Test01");
    printList();

    insertNewNode("Test02");
    printList();

    insertNewNode("Test03");
    printList();

    //releaseList();
    //printList();

    //std::cout << findData("Test003") << std::endl;

    deleteData("Test01");
    printList();
    //deleteData("Test01");

    return 0;
}
