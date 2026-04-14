#include "pch.h"
#include "TimerManager.h"
#include "Timer.h"

HRESULT CTimerManager::ADD_Timer(const string& name)
{
    auto iter = m_TimerList.find(name);
    if (iter == m_TimerList.end())
    {
        CTimer* pTimer = CTimer::Create();
        m_TimerList.emplace(name, pTimer);
        cout << "LOG : ADD Timer : " << name << endl;
    }
    else
    {
        cout << "LOG : Already Timer" << endl;
    }

    return S_OK;
}

void CTimerManager::Remove_Timer(const string& name)
{
    auto iter = m_TimerList.find(name);
    if (iter != m_TimerList.end())
    {
        m_TimerList.erase(iter);
        cout << "LOG : Remove Timer : " << name << endl;
    }
}

CTimerManager* CTimerManager::Create()
{
    CTimerManager* pInstance = new CTimerManager();
    if (FAILED(pInstance->Initialize()))
    {
        delete pInstance;
        pInstance = nullptr;
    }

    return pInstance;
}

float CTimerManager::Get_TimeDelta(const string& strTimerTag)
{
    CTimer* pTimer = Find_Timer(strTimerTag);
    if (nullptr == pTimer)
        return 0.f;

    pTimer->Update_Timer();
    return pTimer->Get_TimeDelta();
}

HRESULT CTimerManager::Initialize()
{

    return S_OK;
}

CTimer* CTimerManager::Find_Timer(const string& name)
{
    auto iter = m_TimerList.find(name);
    if (iter == m_TimerList.end())
        return nullptr;

    return iter->second;
}
