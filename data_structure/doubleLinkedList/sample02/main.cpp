//
// Created by bong on 2023-02-16.
//


#include <iostream>
#include <string>

namespace dll2{

    typedef struct USERDATA{
        // 멤버 함수 포인터
        const char* (*getKey)(void*);

        char szName[64];  //key
        char szPhone[64];
    } USERDATA;

    const char * getKeyFromUserData(void *pUser){
        ;
        return ((USERDATA*) pUser)->szName;
    }

    USERDATA* createUserData(const char* pszName, const char* pszPhone){
        USERDATA* pNewData = (USERDATA*) malloc(sizeof(USERDATA));
        memset(pNewData, 0, sizeof(USERDATA));
        strcpy_s(pNewData->szName, sizeof(pNewData->szName), pszName);
        strcpy_s(pNewData->szPhone, sizeof(pNewData->szPhone), pszPhone);

        pNewData->getKey = getKeyFromUserData;

        return pNewData;
    }

    typedef struct NODE {
        // 관리 대상 자료
        void* pData;

        // 자료구조
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

        g_pHead->next = g_pTail;
        g_pTail->prev = g_pHead;
    }


    void releaseList(){
        NODE* pTmp = g_pHead->next;

        while(pTmp != g_pTail){
            NODE* pDelete = pTmp; // back up!!
            pTmp = pTmp->next;

            //printf("free [%p], data: %s \n", pDelete, pDelete->pszData);

            free(pDelete->pData);
            free(pDelete);
        }
        std::cout << std::endl;

        g_pHead->next = g_pTail;
        g_pTail->prev = g_pHead;
        g_nSize = 0;
    }

    void printList(){
        NODE* pTmp = g_pHead;
        int i= 0;

        printf("PrintList(): g_nSize: %d, g_pHead [%p], g_pTail [%p]\n", g_nSize, g_pHead, g_pTail);
        while(pTmp != nullptr){
            if(pTmp == g_pHead || pTmp == g_pTail){
                printf("Prev: [%p] | Cur: [%p] | Next: [%p]\n",
                        pTmp->prev, pTmp, pTmp->next);
            }else{
                USERDATA* pUser = (USERDATA*)pTmp->pData;
                printf("Index: %d | Prev: [%p] | Cur: [%p], Data: %s | Next: [%p]\n",
                       i, pTmp->prev, pTmp,
                       pUser->getKey(pTmp->pData),
                       pTmp->next);
                i++;
            }
            pTmp = pTmp->next;
        }
        std::cout << std::endl;
    }

    NODE* findNode(const char* pszKey){
        NODE* pTmp = g_pHead->next;
        const char* (*pfGetKey)(void*) = nullptr;
        while (pTmp != g_pTail){
            pfGetKey = getKeyFromUserData;
            if(strcmp(pfGetKey(pTmp->pData), pszKey)==0)
                return pTmp;

            pTmp = pTmp->next;
        }

        return nullptr;
    }

    void insertBefore(NODE *pNode, void* pParam) {

        NODE* pNewNode = (NODE*) malloc(sizeof(NODE));
        memset(pNewNode, 0, sizeof(NODE));
        //strcpy_s(pNewNode->pszData, sizeof(pNewNode->pszData), data);
        pNewNode->pData = (USERDATA*) pParam;
        //pNewNode->getKey = pfParam;

        pNewNode->prev = pNode->prev;
        pNewNode->next = pNode;

        pNode->prev = pNewNode;
        pNewNode->prev->next = pNewNode;

        g_nSize++;
    }

    int deleteNode(const char* pszKey){
        NODE* pNode = findNode(pszKey);

        pNode->prev->next = pNode->next;
        pNode->next->prev = pNode->prev;

        printf("deleteNode: [%p]\n", pNode);
        free(pNode->pData);
        free(pNode);

        g_nSize--;

        return 0;
    }

    int insertAtHead(void* pParam){

        NODE* pNewNode = (NODE*) malloc(sizeof(NODE));
        memset(pNewNode, 0, sizeof(NODE));

        {
            // 관리 대상 자료에 관한 초기화
            pNewNode->pData = (USERDATA*) pParam;
        }

        {
            // 연결 리스트에 관한 초기화
            pNewNode->next = g_pHead->next;
            pNewNode->prev = g_pHead;

            g_pHead->next = pNewNode;
            pNewNode->next->prev = pNewNode;

            g_nSize++;
        }

        return g_nSize;
    }

    int insertAtTail(void* pParam){
        insertBefore(g_pTail, pParam);
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


    int insertAt(int idx, void* pParam,  const char* (*pfParam)(void*)){
        int i = 0;
        NODE* pTmp = g_pHead->next;
        while(pTmp != g_pTail){

            if(i == idx){
                insertBefore(pTmp, pParam);
                return i;
            }

            pTmp = pTmp->next;
            i++;
        }
        insertAtTail(pParam);

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
    using namespace dll2;

    initList();
    printList();

    USERDATA* data = nullptr;
    data = createUserData("PGB", "010-000-0000");
    insertAtTail(data);

    data = createUserData("TEST", "010-111-1111");
    insertAtTail(data);
    printList();

    releaseList();
    printList();


    return 0;
}