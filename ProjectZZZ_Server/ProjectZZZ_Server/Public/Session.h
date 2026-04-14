#pragma once

#include "Server_Defines.h"

class   CPlayer;
struct  Player_Data;

class CSession
{
public :
    int                     Get_ID() { return m_hostID; }

    void                    Set_Poisition(float x, float y, float z);
    void                    Set_NickName(const string& szName);
    void                    Set_Level(int iLevel);
    void                    Set_Dead();
    const Player_Data*      Get_Info();

private:
    int                     m_hostID;
    CPlayer*                m_pPlayer = nullptr;

public :
    static CSession*        Create(int HostID);
    void                    Release();

private :
    CSession();
    HRESULT                Initialize(int HostID);
};