// ProjectZZZ_Server.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include "ServerManager.h"

int main()
{
    // 서버를 연다.
    // 서버의 파라미터 받을 객체
    ErrorInfoPtr Error;
    CServerManager::Get_Instance(Error);
    if (Error != nullptr)
        return 1;

    while (true)
    {
        Sleep(1000);
    }

    return 0;
   
}