#pragma once

#include "Server_Defines.h"

class CCustom_Stub;
class CTimerManager;
class CServer_Event;
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
    
    void                    Update(float fTime);

#pragma region Session
    void                    ADD_JoinClient(int hostID, shared_ptr<CSession> ClientData, LOGIN_MSG Msg);
    void                    Leave_Client(int ClientID);
    void                    Clear_DeadClient();
#pragma endregion

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
    bool                    Login_EXcuteDB(int ClientID, int LoginType, string ID, string Password, string uid, string email);
    bool                    Request_UniqueNickName(int ClientID, string NickName);
#pragma endregion

#pragma region Add_Item
    void                    ADD_Gold(int iHostID, int Amount);
    int                     ADD_Item(int iHostID, int ItemID, int ItemCount);
#pragma endregion


    Proxy*                  Get_Proxy()     { return m_pProxy; }
    void                    Release_Server();

private :
    void                    Initalized(ErrorInfoPtr Error);
   

private :
    static CServerManager*              m_pGameInstance;

    unordered_map<int, shared_ptr<CSession>>            m_SessionList;
    shared_ptr<class CDBManager>                        m_pDBManager = nullptr;
    shared_ptr<class CMapManager>                       m_pMapManager = nullptr;

    Deque<string>                       m_ChatList;
    vector<string>                      m_NewChat;

    Proxy*                              m_pProxy = nullptr;
    CCustom_Stub*                       m_pStub = nullptr;
    CNetServer*                         m_pServer = nullptr;
    CServer_Event*                      m_pEvent = nullptr;
};

