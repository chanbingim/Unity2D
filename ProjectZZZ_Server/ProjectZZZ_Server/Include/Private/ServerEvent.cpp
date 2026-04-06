#include "pch.h"
#include "ServerEvent.h"
#include "ServerManager.h"

void CServer_Event::OnClientJoin(CNetClientInfo* clientInfo)
{
    if (3 > clientInfo->m_HostID)
        return;

	cout << "Join : " << clientInfo->m_HostID << endl;
    CServerManager* pInstance = CServerManager::Get_Instance();

    Player* pPlayer = new Player();
    pPlayer->iLevel = 1;
    pPlayer->hostID = clientInfo->m_HostID;
    pPlayer->NickName = '0' + clientInfo->m_HostID;
    pPlayer->PosX = 0;
    pPlayer->PosY = 0;
    pPlayer->PosZ = 0;
    pInstance->ADD_JoinClient(pPlayer);

    auto pProxy = pInstance->Get_Proxy();
    pProxy->OnPlayerJoined(clientInfo->m_HostID, RmiContext::ReliableSend, (int)clientInfo->m_HostID, 0, 0, 0);
}

void CServer_Event::OnClientLeave(CNetClientInfo* clientInfo, ErrorInfo* errorinfo, const ByteArray& comment)
{
	cout << "Levae : " << clientInfo->m_HostID << endl;
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
