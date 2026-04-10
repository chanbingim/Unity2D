#include "pch.h"
#include "ServerManager.h"
#include "ServerEvent.h"

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
    for (auto& iter : m_PlayerList)
        delete iter.second;

    delete  m_pProxy;
    m_pStub->Release();
    m_PlayerList.clear();
}

void CServerManager::ADD_JoinClient(Player* ClientData)
{
    auto iter = m_PlayerList.find(ClientData->hostID);
    if (iter == m_PlayerList.end())
    {
        m_PlayerList.emplace(ClientData->hostID, ClientData);
        m_pProxy->OnPlayerJoined((HostID)ClientData->hostID, RmiContext::ReliableSend, ClientData->hostID, 0, 0, 0);

        cout << "Join Player : " << ClientData->NickName << endl;
    }
    else
    {
        cout << "AlReady Join Player : " << ClientData->NickName << endl;
    }
}

void CServerManager::Leave_Client(int ClientID)
{
    auto iter = m_PlayerList.find(ClientID);
    if (iter != m_PlayerList.end())
    {
        // 여기서 나간 클라이언트를 제외한 모두에게 이벤트 호출을 통해서 알려주자.
        iter->second->bIsDead = true;
    }
}

void CServerManager::Update_Player(HostID ID, float PosX, float PosY, float PosZ)
{
    auto iter = m_PlayerList.find(ID);
    if (iter != m_PlayerList.end())
    {
        iter->second->PosX = PosX;
        iter->second->PosY = PosY;
        iter->second->PosZ = PosZ;
    }
}

void CServerManager::ADD_Chat(HostID ID, string Text)
{
    auto iter = m_PlayerList.find(ID);
    if (iter != m_PlayerList.end())
    {
        string Chat = iter->second->NickName + " : " + Text;
        m_NewChat.push(Chat);
        cout << "Log ChatMsg :" << Chat << endl;
    }
}

void CServerManager::Clear_Chat()
{
    m_ChatList.clear();
}

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

    m_ChatList.reserve(1000);
    if (Error != nullptr)
        cout << "Server start failed: " << Error->ToString().GetString() << endl;
    else
        cout << "Server started on UDP 33334" << endl;
}

void CServerManager::Update(float fTime)
{
   // Tick처리를 위한 데이터를 여기서 뿌리자
   
    HostID clientList[256];
    int count = m_pServer->GetClientHostIDs(clientList, 256);

    // 여기서 서버의 1FPS 마다 처리
    // 일단 접속된 클라이언트의 좌표를 모두 뿌려보자
    for (auto& iter : m_PlayerList)
    {
        Player* pPlayer = iter.second;
        for (int i = 0; i < count; i++)
        {
            double Latency = m_pServer->GetRecentPingSec(clientList[i]);
            m_pProxy->OnOtherPlayerUpdated(clientList[i], RmiContext::ReliableSend, pPlayer->hostID, pPlayer->NickName, pPlayer->PosX, pPlayer->PosY, pPlayer->PosZ);

            while (!m_NewChat.empty())
                m_pProxy->OnChat(clientList[i], RmiContext::ReliableSend, clientList[i], m_NewChat.front());
        }
    }

    while (!m_NewChat.empty())
        m_NewChat.pop();
}

void CServerManager::Update_Proxy()
{
    
}

void CServerManager::Clear_DeadClient()
{
    for (auto iter = m_PlayerList.begin();  iter != m_PlayerList.end();)
    {
        if (iter->second->bIsDead)
        {
            delete iter->second;
            iter = m_PlayerList.erase(iter);
        }
        else
            iter++;
    }
}