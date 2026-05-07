#pragma once
#include "Server_Defines.h"

class CPlayer
{
public :
    enum class STATE_TYPE {
        IDLE = 0, WALK, RUN, ATTACK, DEAD, END
    };

public:
    const PLAYER_DATA*      Get_Info() { return &m_pInfo; }
    const STATE_TYPE&       Get_AnimSate() { return m_AnimState; }
    float                   Get_AnimTime() { return m_fAnimTime; }

    void                    Set_Info(const PLAYER_DATA* pinfo);

    // Transform
    void                    Set_Scale(float x, float y, float z);
    void                    Set_Rotation(float x, float y, float z, float w);
    void                    Set_Poisition(float x, float y, float z);

    void                    Set_NickName(const string& szName);
    void                    Set_AnimSate(STATE_TYPE state, float fTime = 0.f);
    void                    Set_Level(int iLevel);
    void                    Set_Dead();
     
private:
    PLAYER_DATA             m_pInfo;

    STATE_TYPE              m_AnimState = STATE_TYPE::END;
    float                   m_fAnimTime = 0.f;

public :
    static CPlayer*         Create();
    void                    Release();

private :
    CPlayer();
    HRESULT                 Initialize();

};

