#include "pch.h"
#include "ServerManager.h"
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
    {
        iter.second->Release();
        delete iter.second;
    }

    delete  m_pProxy;
    m_pStub->Release();
    m_SessionList.clear();
    m_pServer->Stop();
}

void CServerManager::ADD_JoinClient(CSession* ClientData)
{
    int hostID = ClientData->Get_ID();
    auto iter = m_SessionList.find(hostID);
    if (iter == m_SessionList.end())
    {
        m_SessionList.emplace(hostID, ClientData);
        m_pProxy->OnPlayerJoined((HostID)hostID, RmiContext::ReliableSend, hostID, 0, 0, 0);
    }
    else
    {
        cout << "AlReady Join Player ID : " << hostID << endl;
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

void CServerManager::Update_Player(HostID ID, float PosX, float PosY, float PosZ)
{
    auto iter = m_SessionList.find(ID);
    if (iter != m_SessionList.end())
        iter->second->Set_Poisition(PosX, PosY, PosZ);
}

void CServerManager::ADD_Chat(HostID ID, string Text)
{
    auto iter = m_SessionList.find(ID);
    if (iter != m_SessionList.end())
    {
        string Chat = iter->second->Get_Info()->m_NickName + " : " + Text;
        m_NewChat.push_back(Chat);
        cout << "Log ChatMsg -" << Chat << endl;
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

    m_NewChat.reserve(1000);
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
    for (auto& iter : m_SessionList)
    {
        CSession* pSession = iter.second;
        const Player_Data* pPlayer_Info = pSession->Get_Info();

        for (int i = 0; i < count; i++)
        {
            double Latency = m_pServer->GetRecentPingSec(clientList[i]);
            m_pProxy->OnOtherPlayerUpdated(clientList[i], RmiContext::ReliableSend,
                pSession->Get_ID(), pPlayer_Info->m_NickName, pPlayer_Info->m_PosX,
                pPlayer_Info->m_PosY, pPlayer_Info->m_PosZ);

            for(auto& Text : m_NewChat)
                m_pProxy->OnChat(clientList[i], RmiContext::ReliableSend, clientList[i], Text);
        }
    }

    m_NewChat.clear();
}

void CServerManager::Update_Proxy()
{
    
}

void CServerManager::Clear_DeadClient()
{
    for (auto iter = m_SessionList.begin();  iter != m_SessionList.end();)
    {
        CSession* pSession = iter->second;
        const Player_Data* pPlayer_Info = pSession->Get_Info();

        if (pPlayer_Info->m_bIsDead)
        {
            delete iter->second;
            iter = m_SessionList.erase(iter);
        }
        else
            iter++;
    }
}