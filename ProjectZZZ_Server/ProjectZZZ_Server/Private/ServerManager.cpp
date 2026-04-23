#include "pch.h"
#include "ServerManager.h"

#include "DBManager.h"
#include "MapManager.h"

#include "ServerEvent.h"
#include "Session.h"
#include "Player.h"

CServerManager*  CServerManager::m_pGameInstance = nullptr;

CServerManager::CServerManager()
{
}

CServerManager::~CServerManager()
{
}

CServerManager* CServerManager::Get_Instance(ErrorInfoPtr Error)
{
    if (nullptr == m_pGameInstance)
    {
        m_pGameInstance = new CServerManager();
        m_pGameInstance->Initalized(Error);
    }

    return m_pGameInstance;
}

CServerManager* CServerManager::Get_Instance()
{
    return m_pGameInstance;
}

void CServerManager::Release_Server()
{
    for (auto& iter : m_SessionList)
        iter.second->Release();

    m_pMapManager->Release();
    m_pDBManager->Release();

    m_pStub->Release();
    m_SessionList.clear();
    m_pServer->Stop();

    delete  m_pProxy;
}

#pragma region DB
bool CServerManager::Login_EXcuteDB(int ClientID, string ID, string Password)
{
    if (m_pDBManager)
        return m_pDBManager->Login_EXcuteDB(ClientID, ID, Password);

    return false;
}

bool CServerManager::Request_UniqueNickName(int ClientID, string NickName)
{
    COdbcRecordset Record;

    if (m_pDBManager)
        return m_pDBManager->Request_UniqueNickName(ClientID, NickName);

    return false;
}
#pragma endregion

#pragma region Client_Event
void CServerManager::ADD_JoinClient(int hostID, shared_ptr<CSession> ClientData, LOGIN_MSG Msg)
{
    try
    {
        if (nullptr == ClientData)
            throw runtime_error("Log : Login Fail");

        int hostID = ClientData->Get_ID();
        auto iter = m_SessionList.find(hostID);
        if (iter == m_SessionList.end())
        {
            PLAYER_DATA Player_Data;
            Player_Data.fPosX = Player_Data.fPosY = Player_Data.fPosZ = 0;

            if (m_pDBManager)
            {
                if (!m_pDBManager->RequestLoadPlayerData(ClientData->Get_TableID(), Player_Data))
                {
                    cout << "Not Find Character Data : " << hostID << endl;
                    /*
                    *   나중에 여기서 캐릭터 생성 로직으로 분기
                    */

                    return;
                }
                else
                {
                    ClientData->Set_Info(&Player_Data);
                    m_SessionList.emplace(hostID, ClientData);
                    m_pProxy->ResponseLoginEvent((HostID)hostID, RmiContext::ReliableSend, true, static_cast<int>(Msg));
                    //m_pProxy->OnPlayerJoined((HostID)hostID, RmiContext::ReliableSend, hostID, Player_Data.szName, Player_Data.fPosX, Player_Data.fPosY, Player_Data.fPosZ);
                }
            }
        }
        else
        {
            cout << "AlReady Join Player ID : " << hostID << endl;
        }
    }
    catch (const exception& Error)
    {
        cout << "Error: " << Error.what() << endl;
        m_pProxy->ResponseLoginEvent((HostID)hostID, RmiContext::ReliableSend, false, static_cast<int>(Msg));
    }
}

void CServerManager::Leave_Client(int ClientID)
{
    auto iter = m_SessionList.find(ClientID);
    if (iter != m_SessionList.end())
    {
        // 여기서 나간 클라이언트를 제외한 모두에게 이벤트 호출을 통해서 알려주자.
        iter->second->Set_Dead();
    }
}

void CServerManager::Spawn_Player(const int clientId, const int iLevelID)
{
    auto iter = m_SessionList.find(clientId);
    if (iter != m_SessionList.end())
    {
        m_pMapManager->Join_Level(iter->second, iLevelID);
    }
}

void CServerManager::Clear_DeadClient()
{
    for (auto iter = m_SessionList.begin(); iter != m_SessionList.end();)
    {
        CSession* pSession = iter->second.get();
        const Player_Data* pPlayer_Info = pSession->Get_Info();

        if (pPlayer_Info->bIsDead)
            iter = m_SessionList.erase(iter);
        else
            iter++;
    }
}
#pragma endregion

void CServerManager::Update_Player(HostID ID, float PosX, float PosY, float PosZ)
{
    auto iter = m_SessionList.find(ID);
    if (iter != m_SessionList.end())
        iter->second->Set_Poisition(PosX, PosY, PosZ);
}

void CServerManager::Update_PlayerAnimation(HostID ID, int iAnimState, float fTime)
{
    auto iter = m_SessionList.find(ID);
    if (iter != m_SessionList.end())
        iter->second->Set_AnimState(iAnimState, fTime);
}

#pragma region Chat
void CServerManager::ADD_Chat(HostID ID, string Text)
{
    auto iter = m_SessionList.find(ID);
    if (iter != m_SessionList.end())
    {
        string Chat = iter->second->Get_Info()->szName + " : " + Text;
        m_NewChat.push_back(Chat);
        cout << "Log ChatMsg -" << Chat << endl;
    }
}

void CServerManager::Clear_Chat()
{
    m_ChatList.clear();
}
#pragma endregion

void CServerManager::Initalized(ErrorInfoPtr Error)
{
    m_pServer = CNetServer::Create();
    m_pEvent = CServer_Event::Create();
    m_pServer->SetEventSink(m_pEvent);

    CStartServerParameter   param;
    param.m_tcpPorts.push_back(33334);

    m_pProxy = new Proxy();
    m_pStub = CCustom_Stub::Create();

    m_pServer->AttachProxy(m_pProxy);
    m_pServer->AttachStub(m_pStub);
    m_pServer->Start(param, Error);

    m_pDBManager = make_shared<CDBManager>();
    m_pMapManager = make_shared<CMapManager>();

    m_NewChat.reserve(1000);
    if (Error != nullptr)
        cout << "Server start failed: " << Error->ToString().GetString() << endl;
    else
        cout << "Server started on UDP 33334" << endl;
}

void CServerManager::Update(float fTime)
{
   // Tick처리를 위한 데이터를 여기서 뿌리자
    m_pDBManager->Update_DB(m_pProxy);
    m_pMapManager->Update();

    HostID clientList[256];
    int count = m_pServer->GetClientHostIDs(clientList, 256);

    // 여기서 서버의 1FPS 마다 처리
    // 일단 접속된 클라이언트의 좌표를 모두 뿌려보자
    for (auto& iter : m_SessionList)
    {
        CSession* pSession = iter.second.get();
        const PLAYER_DATA* pPlayer_Info = pSession->Get_Info();

        for (int i = 0; i < count; i++)
        {
            for(auto& Text : m_NewChat)
                m_pProxy->OnChat(clientList[i], RmiContext::ReliableSend, clientList[i], Text);
        }
    }

    
    m_NewChat.clear();
}