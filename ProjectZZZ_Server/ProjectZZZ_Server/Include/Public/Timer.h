#pragma once

// 프라우드넷의 CPU타임을 이용하기 위해서 Timer를 제작한다
#include "Server_Defines.h"

class CTimer
{
private:
    CTimer();
    virtual ~CTimer() = default;

public:
    float	Get_TimeDelta() const { return m_fTimeDelta; }

public :
    void                Update_Timer();

private :
    HRESULT	            Initialize();

private:
    LARGE_INTEGER		m_FrameTime{};
    LARGE_INTEGER		m_FixTime{};
    LARGE_INTEGER		m_LastTime{};
    LARGE_INTEGER		m_CpuTick{};

    float				m_fTimeDelta{};

public:
    static  CTimer*     Create();
    void                Release();
};

