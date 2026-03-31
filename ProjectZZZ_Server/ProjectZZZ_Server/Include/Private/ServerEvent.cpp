#include "pch.h"
#include "ServerEvent.h"

void CServer_Event::OnClientJoin(CNetClientInfo* clientInfo)
{
	cout << "Join : " << clientInfo->m_HostID << endl;
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
