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
bool CServerManager::Login_EXcuteDB(int ClientID, int LoginType, string ID, string Password, string uid, string email)
{
    if (m_pDBManager)
        return m_pDBManager->Login_EXcuteDB(ClientID, LoginType, ID, Password, uid, email);

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

#pragma region Player
void CServerManager::ADD_Gold(int iHostID, int Amount)
{
    auto iter = m_SessionList.find(iHostID);
    if (iter == m_SessionList.end())
        return;

    CPlayer* pPlayer = iter->second->GetPlayer();
    pPlayer->ADD_Gold(Amount);
    m_pProxy->Response_Gold((HostID)iHostID, RmiContext::ReliableSend, iHostID, pPlayer->Get_Gold());
}

bool CServerManager::ADD_Item(int iHostID, int ItemID, int ItemCount)
{
    auto iter = m_SessionList.find(iHostID);
    if (iter == m_SessionList.end())
        return -1;

    ITEM_DATA Data;

    m_pDBManager->Connection_DB("item_db");
    m_pDBManager->Request_ItemData(ItemID, Data);

    int AliveItemCnt = iter->second->GetPlayer()->Picked_Item(Data, ItemCount);
    if (-1 != AliveItemCnt || AliveItemCnt == ItemCount)
        return false;

    iter->second->Update_HostInventory();
    return true;
}

bool CServerManager::Remove_Item(int iHostID, int ItemID, int SlotIndex, int ItemCount)
{
    auto iter = m_SessionList.find(iHostID);
    if (iter == m_SessionList.end())
        return -1;

    ITEM_DATA Data;

    m_pDBManager->Connection_DB("item_db");
    m_pDBManager->Request_ItemData(ItemID, Data);
    if (!iter->second->GetPlayer()->Remove_Item(Data, SlotIndex, ItemCount))
        return false;

    iter->second->Update_HostInventory();
    return true;
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

            
            Player_Data.Transform.vRotation = Vector4::Zero;
            Player_Data.Transform.vPosition = Vector3::Zero;

            if (m_pDBManager)
            {
                if (!m_pDBManager->RequestLoadPlayerData(ClientData->Get_TableID(), Player_Data))
                {
                    cout << "Not Find Character Data : " << hostID << endl;

                    return;
                }
                else
                {
                    Player_Data.Transform.vScale = Vector3::One;
                    ClientData->Set_Info(&Player_Data);
                    m_SessionList.emplace(hostID, ClientData);
                    m_pProxy->ResponseLoginEvent((HostID)hostID, RmiContext::ReliableSend, true, static_cast<int>(Msg));
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
        // ���⼭ ���� Ŭ���̾�Ʈ�� ������ ��ο��� �̺�Ʈ ȣ���� ���ؼ� �˷�����.
        iter->second->Set_Dead();
        m_pDBManager->SaveHostData(iter->second.get());

        m_SessionList.erase(iter);
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
    Vector3 vPos(PosX, PosY, PosZ);
    auto iter = m_SessionList.find(ID);
    if (iter != m_SessionList.end())
    {
        CPlayer* pPlayer = iter->second->GetPlayer();
        pPlayer->Set_Poisition(PosX, PosY, PosZ);
    }
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
    if(FAILED(m_pDBManager->Initialize()))
        return;

    m_pMapManager = make_shared<CMapManager>();
    if (FAILED(m_pMapManager->Initialize()))
        return;

    m_NewChat.reserve(1000);
    if (Error != nullptr)
        cout << "Server start failed: " << Error->ToString().GetString() << endl;
    else
        cout << "Server started on TCP 33334" << endl;
}

void CServerManager::Server_DataUpdate(float fTime)
{
    m_pDBManager->Update_DB(m_pProxy);

    for (auto& iter : m_SessionList)
        m_pDBManager->SaveHostData(iter.second.get());
}

void CServerManager::Update(float fTime)
{

    HostID clientList[256];
    int count = m_pServer->GetClientHostIDs(clientList, 256);

    for (auto& Text : m_NewChat)
    {
        m_pProxy->OnChat(clientList, count, RmiContext::ReliableSend, count, Text);
    }

    m_NewChat.clear();

    Server_DataUpdate(fTime);
    m_pMapManager->Update();
}