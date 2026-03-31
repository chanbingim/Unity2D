#pragma once
#include "INetServerEvent.h"

class CServer_Event : public INetServerEvent
{
public :
    // 클라이언트 접속
    void OnClientJoin(CNetClientInfo* clientInfo) override;

    // 클라이언트 접속 비활성화
    void OnClientLeave(CNetClientInfo* clientInfo, ErrorInfo* errorinfo, const ByteArray& comment) override;

    void OnError(ErrorInfo* errorInfo) override;
    void OnWarning(ErrorInfo* errorInfo) override;
    void OnInformation(ErrorInfo* errorInfo) override;
    void OnException(const Exception& e) override;
    void OnNoRmiProcessed(RmiID rmiID) override;
    void OnP2PGroupJoinMemberAckComplete(HostID groupHostID, HostID memberHostID, ErrorType result) override;
    void OnUserWorkerThreadBegin() override;
    void OnUserWorkerThreadEnd() override;
};