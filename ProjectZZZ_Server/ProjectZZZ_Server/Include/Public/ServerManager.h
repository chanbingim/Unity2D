#pragma once

#include "Server_Defines.h"

class CCustom_Stub;
class CTimerManager;
class CServer_Event;

using namespace ServerToClient;

struct Player
{
    int         hostID;
    string      NickName;
    bool        bIsDead = false;

    int         iLevel;
    float       PosX, PosY, PosZ;
};

class CServerManager
{
private :
    CServerManager();
    ~CServerManager();

public :
    static  CServerManager* Get_Instance(ErrorInfoPtr Error);
    static  CServerManager* Get_Instance();
    
    void                    Release_Server();

    void                    ADD_JoinClient(Player* ClientData);
    void                    Leave_Client(int ClientID);

    void                    Update_Player(HostID ID, float PosX, float PosY, float PosZ);

    void                    Update(float fTime);
    void                    Update_Proxy();
    void                    Clear_DeadClient();

    Proxy*                  Get_Proxy()     { return m_pProxy; }

private :
    void                    Initalized(ErrorInfoPtr Error);

private :
    static CServerManager*              m_pGameInstance;
    unordered_map<int, Player*>         m_PlayerList;

    Proxy*                  m_pProxy = nullptr;
    CCustom_Stub*           m_pStub = nullptr;
    CNetServer*             m_pServer = nullptr;
    CServer_Event*          m_pEvent = nullptr;
};

