#pragma once
#include "Server_Defines.h"

class CActor;
class CSession;

class CLevel
{
public :
    void                Join_Session(shared_ptr<CSession> pSession);
    void                Join_Actor(shared_ptr<CActor> pActor);

    void                Update();


private :
    int                         m_iLevelID;

    list<weak_ptr<CSession>>    m_JoinedSession;
    list<weak_ptr<CActor>>      m_ActorList;
    ServerToClient::Proxy*      m_pProxy = nullptr;

private :
    CLevel();
    CLevel(int iID);
    HRESULT             Initialize();

public :
    static CLevel*      Create(int iLevelID);

};

