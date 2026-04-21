#pragma once

#include "Server_Defines.h"

class CCustom_Stub;
class CTimerManager;
class CServer_Event;
class CDBManager;
class CSession;

using namespace ServerToClient;

class CServerManager
{
private :
    CServerManager();
    ~CServerManager();

public :
    static  CServerManager* Get_Instance(ErrorInfoPtr Error);
    static  CServerManager* Get_Instance();
    
    void                    Release_Server();
    void                    Leave_Client(int ClientID);

#pragma region Spawn Actor
    void                    Spawn_Player(const int clientId, const int iLevelID);

#pragma endregion

#pragma region Update_PlayerData
    void                    Update_Player(HostID ID, float PosX, float PosY, float PosZ);
    void                    Update_PlayerAnimation(HostID ID, int iAnimState, float fTime);

#pragma endregion

#pragma region Chat
    void                    ADD_Chat(HostID ID, string Text);
    void                    Clear_Chat();
#pragma endregion

#pragma region DB
    bool                    Login_EXcuteDB(int ClientID, string ID, string Password);
    bool                    Request_UniqueNickName(int ClientID, string NickName);
#pragma endregion

    void                    ADD_JoinClient(int hostID, CSession* ClientData, LOGIN_MSG Msg);

    void                    Update(float fTime);
    void                    Clear_DeadClient();

    Proxy*                  Get_Proxy()     { return m_pProxy; }

private :
    void                    Initalized(ErrorInfoPtr Error);
   

private :
    static CServerManager*              m_pGameInstance;
    unordered_map<int, CSession*>       m_SessionList;

    CDBManager*                         m_pDBManager;
    Deque<string>                       m_ChatList;
    vector<string>                      m_NewChat;

    Proxy*                              m_pProxy = nullptr;
    CCustom_Stub*                       m_pStub = nullptr;
    CNetServer*                         m_pServer = nullptr;
    CServer_Event*                      m_pEvent = nullptr;
};

