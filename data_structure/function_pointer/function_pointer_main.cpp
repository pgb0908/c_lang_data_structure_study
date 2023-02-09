//
// Created by bong on 2023-02-09.
//


#include <cstdio>
#include <functional>

int _cdecl test(int a){
    printf("Hello World\n");

    return 0;
}

int main(){

    // todo c++ custom calling convention 알아보기

    //test(19);
    int (_cdecl *pfTest)(int) = test;
    auto funcPtr = test;
    std::function<int(int)> function = test;

    //pfTest(4);
    function(3);

    return 0;
}