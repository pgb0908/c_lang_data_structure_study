
#include <Windows.h>
#include "iostream"

DWORD WINAPI ThreadFunction(LPVOID pParam){
    std::cout << "   begin thread " << std::endl;

    for(int i=0; i< 5; ++i){
        printf("   [Worker thread] %d\n", i);
        ::Sleep(1);
    }

    std::cout << "   before exit-event set " << std::endl;
    // 이 함수를 호출하면 _tmain() 함수의
    // WaitForSigleObject() 함수가 반환함
    ::SetEvent((HANDLE) pParam);

    std::cout << "   after exit-event set " << std::endl;
    std::cout << "   Thread end " << std::endl;

    return 0;
}

auto  dd = [](LPVOID pParam)->DWORD WINAPI {
    std::cout << "   begin thread " << std::endl;

    for(int i=0; i< 5; ++i){
        printf("   [Worker thread] %d\n", i);
        ::Sleep(1);
    }

    std::cout << "   before exit-event set " << std::endl;
    // 이 함수를 호출하면 _tmain() 함수의
    // WaitForSigleObject() 함수가 반환함
    ::SetEvent((HANDLE) pParam);

    std::cout << "   after exit-event set " << std::endl;
    std::cout << "   Thread end " << std::endl;

    return 0; };

int main(){
    // 이벤트 객체 생성
    HANDLE hEvent = ::CreateEvent(
            NULL,  // 디폴트 보안 속성 적용
            FALSE,   // 자동으로 상태 전환
            FALSE,     // 초기 상태는 FALSE
            NULL          // 이름 없음
            );

    // 새로운 스레드 생성
    DWORD dwThreadID = 0;
    HANDLE hThread = ::CreateThread(
            NULL,  // 보안 속성 상속
            0,         // 스택 메모리 기본크기 (1mb)
            dd, // 스래드로 실행할 함수 이름
            hEvent,      // 함수에 전달할 매개변수
            0,      // 생성 플래그는 기본값 사용
            &dwThreadID  // 생성된 스레드ID 저장
            );

    for(int i=0; i< 10; ++i){
        printf("[Main thread] %d\n", i);

        if(i ==3 && ::WaitForSingleObject(hEvent, INFINITE) == WAIT_OBJECT_0){
            printf("Detect Event %d\n", i);
            ::CloseHandle(hThread);
            hEvent = NULL;
        }
    }


    return 0;
}
