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

void CServerManager::Initalized(ErrorInfoPtr Error)
{
    m_pServer = CNetServer::Create();

    m_pEvent = new CServer_Event();
    m_pServer->SetEventSink(m_pEvent);

    CStartServerParameter   param;
    param.m_tcpPorts.push_back(33334);

    m_pProxy = new Proxy();
    m_pStub = new CCustom_Stub();

    m_pServer->AttachProxy(m_pProxy);
    m_pServer->AttachStub(m_pStub);
    m_pServer->Start(param, Error);

    if (Error != nullptr)
        cout << "Server start failed: " << Error->ToString().GetString() << endl;
    else
        cout << "Server started on UDP 33334" << endl;
}
