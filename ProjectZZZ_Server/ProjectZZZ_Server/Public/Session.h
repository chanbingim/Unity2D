#pragma once

#include "Server_Defines.h"

class   CPlayer;

class CSession
{
public :
    int                     Get_ID() { return m_hostID; }
    int                     Get_TableID() { return m_TableID; }

    void                    Set_Poisition(float x, float y, float z);
    void                    Set_NickName(const string& szName);
    void                    Set_Level(int iLevel);
    void                    Set_Dead();

    void                    Set_Info(const PLAYER_DATA* pinfo);
    const PLAYER_DATA*      Get_Info();

private:
    int                     m_hostID;
    int                     m_TableID;
    CPlayer*                m_pPlayer = nullptr;

public :
    static CSession*        Create(int HostID, int TableID, PLAYER_DATA* info = nullptr);
    void                    Release();

private :
    CSession();
    HRESULT                Initialize(int HostID, int TableID, PLAYER_DATA* info);
};