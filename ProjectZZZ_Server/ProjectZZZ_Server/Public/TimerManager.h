#pragma once
#include "Server_Defines.h"

class CTimer;

class CTimerManager
{
public :
    HRESULT ADD_Timer(const string& name);
    void    Remove_Timer(const string& name);

public :
    static  CTimerManager*  Create();
    float			        Get_TimeDelta(const string& strTimerTag);

private :
    HRESULT     Initialize();
    CTimer*     Find_Timer(const string& name);

private :
    unordered_map<string, CTimer*>  m_TimerList;

};

