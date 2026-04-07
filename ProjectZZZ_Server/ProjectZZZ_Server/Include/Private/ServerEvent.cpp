#include "pch.h"
#include "ServerEvent.h"
#include "ServerManager.h"

void CServer_Event::OnClientJoin(CNetClientInfo* clientInfo)
{
    if (3 > clientInfo->m_HostID)
        return;

	cout << "Join : " << clientInfo->m_HostID << endl;
    Player* pPlayer = new Player();
    pPlayer->iLevel = 1;
    pPlayer->hostID = clientInfo->m_HostID;
    pPlayer->NickName = '0' + clientInfo->m_HostID;
    pPlayer->PosX = 0;
    pPlayer->PosY = 0;
    pPlayer->PosZ = 0;
    
    m_pServerMgr_Instance->ADD_JoinClient(pPlayer);
}

void CServer_Event::OnClientLeave(CNetClientInfo* clientInfo, ErrorInfo* errorinfo, const ByteArray& comment)
{
	cout << "Levae : " << clientInfo->m_HostID << endl;
    m_pServerMgr_Instance->Leave_Client(clientInfo->m_HostID);
}

void CServer_Event::OnError(ErrorInfo* errorInfo)
{
}

void CServer_Event::OnWarning(ErrorInfo* errorInfo)
{
}

void CServer_Event::OnInformation(ErrorInfo* errorInfo)
{
}

void CServer_Event::OnException(const Exception& e)
{
}

void CServer_Event::OnNoRmiProcessed(RmiID rmiID)
{
}

void CServer_Event::OnP2PGroupJoinMemberAckComplete(HostID groupHostID, HostID memberHostID, ErrorType result)
{
}

void CServer_Event::OnUserWorkerThreadBegin()
{
}

void CServer_Event::OnUserWorkerThreadEnd()
{
}

CServer_Event* CServer_Event::Create()
{
    CServer_Event* pInstance = new CServer_Event();
    if (FAILED(pInstance->Initailize()))
    {
        delete pInstance;
        pInstance = nullptr;
    }

    return pInstance;
}

HRESULT CServer_Event::Initailize()
{
    m_pServerMgr_Instance = CServerManager::Get_Instance();
    return S_OK;
}
