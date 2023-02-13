//
// Created by bong on 2023-02-13.
//

#include "iostream"

typedef struct NODE {
    // 관리될 데이터
    int nData;

    // 데이터 관리를 위한 포인터
    struct NODE* next;
} NODE;

int main() {

    NODE list[5] = {0};

    // 값 초기화
    list[0].nData = 100;
    list[1].nData = 200;
    list[2].nData = 300;
    list[3].nData = 400;
    list[4].nData = 500;

    // 연결 리스트 구조화
    list[0].next = &list[1];
    list[1].next = &list[2];
    list[2].next = &list[3];
    list[3].next = &list[4];
    list[4].next = nullptr;


    for(int i = 0; i < 5; i++){
        printf("List[%d]: %d \n", i, list[i].nData);
    }
    std::cout << std::endl;

    NODE *pTmp = &list[0];

    while(pTmp != nullptr){
        printf("%p: %d \n", pTmp, pTmp->nData);
        pTmp = pTmp->next;
    }

    return 0;
}