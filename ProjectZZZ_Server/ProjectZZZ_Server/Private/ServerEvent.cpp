#include "pch.h"
#include "ServerEvent.h"

#include "ServerManager.h"
#include "Session.h"

void CServer_Event::OnClientJoin(CNetClientInfo* clientInfo)
{
    if (3 > clientInfo->m_HostID)
        return;

	cout << "Join : " << clientInfo->m_HostID << endl;
    CSession*  pSession = CSession::Create(clientInfo->m_HostID);
    m_pServerMgr_Instance->ADD_JoinClient(pSession);
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
