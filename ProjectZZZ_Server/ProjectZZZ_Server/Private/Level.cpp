#include "pch.h"
#include "Level.h"

#include "Session.h"
#include "ServerManager.h"

CLevel::CLevel()
{

}

CLevel::CLevel(int iID) : m_iLevelID(iID)
{

}

HRESULT CLevel::Initialize()
{
    CServerManager* pServerMgr = CServerManager::Get_Instance();
    m_pProxy = pServerMgr->Get_Proxy();

    return S_OK;
}

CLevel* CLevel::Create(int iLevelID)
{
    CLevel* pInstance = new CLevel(iLevelID);
    if (FAILED(pInstance->Initialize()))
    {
        delete pInstance;
        pInstance = nullptr;
    }

    return pInstance;
}

void CLevel::Join_Session(shared_ptr<CSession> pSession)
{
    m_JoinedSession.push_back(pSession);
}

void CLevel::Join_Actor(shared_ptr<CActor> pActor)
{
    m_ActorList.push_back(pActor);
}

void CLevel::Update()
{
    for (auto& session : m_JoinedSession)
    {
        if (auto sp = session.lock())
        {
            CSession* pSession = sp.get();
            int SessionID = pSession->Get_ID();

            for (auto& OtherSession : m_JoinedSession)
            {
                if (auto OtherSp = session.lock())
                {
                    CSession* pOtherSession = OtherSp.get();
                    auto Data = pOtherSession->Get_Info();
                    if (pSession == pOtherSession)
                        continue;

                    m_pProxy->OnOtherPlayerUpdated((HostID)SessionID, RmiContext::ReliableSend, pOtherSession->Get_ID(),
                        Data->szName, Data->fPosX, Data->fPosY, Data->fPosZ);

                    m_pProxy->OnOtherPlayerAnimUpdated((HostID)SessionID, RmiContext::ReliableSend,
                        pOtherSession->Get_ID(), pOtherSession->Get_AnimSate(), pOtherSession->Get_AnimTime());
                }
            }
        }
    }

    for (auto& actor : m_ActorList)
    {
        for (auto& Otheractor : m_ActorList)
        {

        }
    }

}