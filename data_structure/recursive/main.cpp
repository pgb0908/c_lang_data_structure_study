//
// Created by bong on 2023-02-10.
//

#include "iostream"

int test(int val){
    // 재귀함수는 for문과 같다
    // 함수 call stack을 사용한것
    // for(;조건;)
    if(val == 0) return 0;

    std::cout << "value is : " << val << std::endl;
    return test(val-1);
}


int main(){

    test(5);

    return 0;
}