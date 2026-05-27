#include "pch.h"
#include "Server_Defines.h"

#include "ServerManager.h"
#include "TimerManager.h"

int main()
{
    // 서버를 연다.
    // 서버의 파라미터 받을 객체
    ErrorInfoPtr Error;
    auto pInstance = CServerManager::Get_Instance(Error);
    auto pTimerManager = CTimerManager::Create();

    float TimeAcc = 0;
    pTimerManager->ADD_Timer("ServerTimer");
    pTimerManager->ADD_Timer("Timer_Frame");

    if (Error != nullptr)
        return 1;
    
    while (true)
    {
        pInstance->Clear_DeadClient();
        TimeAcc += pTimerManager->Get_TimeDelta("ServerTimer");
        if (TimeAcc >= SaveDataTickTime)
        {
            pInstance->Update(pTimerManager->Get_TimeDelta("Timer_Frame"));
            TimeAcc = 0.f;
        }
    }

    pInstance->Release_Server();
    return 0;
   
}