// ProjectZZZ_Server.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include "ServerEvent.h"

CServer_Event   g_Event;


int main()
{
    // 서버를 연다.
    CNetServer*     m_pServer = CNetServer::Create();
    m_pServer->SetEventSink(&g_Event);

    // 서버의 파라미터 받을 객체
    CStartServerParameter param;

    // 서버 포트 번호 등록
    param.m_tcpPorts.push_back(33334);

    ErrorInfoPtr startError;
    m_pServer->Start(param, startError);
    if (startError != nullptr)
    {
        cout << "Server start failed: " << startError->ToString().GetString() << endl;
        return 1;
    }

    cout << "Server started on TCP 33334" << endl;

    while (true)
    {
        Sleep(1000);
    }

    return 0;
   
}