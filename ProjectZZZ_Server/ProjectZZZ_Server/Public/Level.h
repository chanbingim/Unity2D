#pragma once
#include "Base.h"

class CActor;
class CSession;

class CLevel : public CBase
{
public :
    void                Join_Session(shared_ptr<CSession> pSession);
    void                Join_Actor(shared_ptr<CActor> pActor);

    void                Update();
    bool                Get_Dead();

private :
    int                             m_iLevelID;

    list<shared_ptr<CSession>>      m_JoinedSession;
    list<shared_ptr<CActor>>        m_ActorList;
    ServerToClient::Proxy*          m_pProxy = nullptr;

private :
    HRESULT             Initialize();
    void                Broadcast_Session();
    void                Broadcast_Actor();

public :
    CLevel();
    CLevel(int iID);

    static shared_ptr<CLevel>       Create(int iLevelID);
    void                            Release();

};

