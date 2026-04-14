#pragma once
#include "Server_Defines.h"

struct Player_Data
{
    int         m_iLevel;
    string      m_NickName;

    float       m_PosX, m_PosY, m_PosZ;
    bool        m_bIsDead = false;
};

class CPlayer
{
public :
    enum class STATE_TYPE {
        IDLE = 0, WALK, RUN, ATTACK, DEAD, END
    };

public:
    const Player_Data*      Get_Info() { return &m_pInfo; }

    void                    Set_Poisition(float x, float y, float z);
    void                    Set_NickName(const string& szName);
    void                    Set_Level(int iLevel);
    void                    Set_Dead();
     
private:
    Player_Data             m_pInfo;
    STATE_TYPE              m_AnimState = STATE_TYPE::END;

public :
    static CPlayer*         Create();
    void                    Release();

private :
    CPlayer();
    HRESULT                 Initialize();

};

