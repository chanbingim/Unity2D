#pragma once

#include "Base.h"

class   CPlayer;

class CSession : CBase
{
public :
    int                     Get_ID() { return m_hostID; }
    int                     Get_TableID() { return m_TableID; }

    void                    Set_Poisition(float x, float y, float z);
    void                    Set_NickName(const string& szName);
    void                    Set_MapID(int iMapID);
    void                    Set_Level(int iLevel);
    void                    Set_Dead();
    void                    Set_AnimState(int iAnimState, float fTime);

    void                    Set_Info(const PLAYER_DATA* pinfo);
    int                     Get_AnimSate();
    float                   Get_AnimTime();
    int                     Get_MapID();

    const PLAYER_DATA*      Get_Info();
    CPlayer*                GetPlayer() const { return m_pPlayer.get(); }

private:
    int                     m_hostID;
    int                     m_TableID;
    int                     m_EnterMapID;

    unique_ptr<CPlayer>    m_pPlayer = nullptr;

public :
    static shared_ptr<CSession>     Create(int HostID, int TableID, PLAYER_DATA* info = nullptr);
    virtual void                    Release();

private :
    HRESULT                Initialize(int HostID, int TableID, PLAYER_DATA* info);
};