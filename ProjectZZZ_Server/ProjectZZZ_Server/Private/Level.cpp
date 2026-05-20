#include "pch.h"
#include "Level.h"

#include "Session.h"
#include "Player.h"
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

void CLevel::Broadcast_Session()
{
    for (auto& pSession : m_JoinedSession)
    {
        const PLAYER_DATA* Data = pSession->Get_Info();
        const Transform* Transform = &Data->Transform;

        HostID* HostList = pSession->GetPlayer()->Get_HostList();
        int     iHostCount = pSession->GetPlayer()->Get_Hosts();
        int     SessionHostID = pSession->Get_ID();

        m_pProxy->OtherPlayerTransformUpdated(HostList, iHostCount, RmiContext::UnreliableSend, SessionHostID, Data->szName,
            Transform->vScale.X, Transform->vScale.Y, Transform->vScale.Z,
            Transform->vRotation.X, Transform->vRotation.Y, Transform->vRotation.Z, Transform->vRotation.W,
            Transform->vPosition.X, Transform->vPosition.Y, Transform->vPosition.Z);

        m_pProxy->OnOtherPlayerAnimUpdated(HostList, iHostCount, RmiContext::UnreliableSend,
            SessionHostID, pSession->Get_AnimSate(), pSession->Get_AnimTime());
    }
}

void CLevel::Broadcast_Actor()
{
    for (auto actor = m_ActorList.begin(); actor != m_ActorList.end();)
    {
        for (auto& session : m_JoinedSession)
        {
            int SessionID = session->Get_ID();

           /* m_pProxy->OnOtherActorUpdated((HostID)SessionID, RmiContext::ReliableSend, OtherSession->Get_ID(),
                Data->szName, Data->fPosX, Data->fPosY, Data->fPosZ);

            m_pProxy->OnOtherActorAnimUpdated((HostID)SessionID, RmiContext::ReliableSend,
                OtherSession->Get_ID(), OtherSession->Get_AnimSate(), OtherSession->Get_AnimTime());*/
        }
        actor++;
    }
}

shared_ptr<CLevel> CLevel::Create(int iLevelID)
{
    shared_ptr<CLevel> pInstance = make_shared<CLevel>(iLevelID);
    if (FAILED(pInstance->Initialize()))
        pInstance = nullptr;

    return pInstance;
}

void CLevel::Release()
{

}

void CLevel::Join_Session(shared_ptr<CSession> pSession)
{
    m_JoinedSession.push_back(pSession);

    int ClientID = pSession->Get_ID();

    const Player_Data* pPlayer_Info = pSession->Get_Info();
    const Transform* Transform = &pPlayer_Info->Transform;

    m_pProxy->OnPlayerJoined((HostID)ClientID, RmiContext::ReliableSend, ClientID,
        pPlayer_Info->szName, Transform->vPosition.X, Transform->vPosition.Y, Transform->vPosition.Z);
}

void CLevel::Join_Actor(shared_ptr<CActor> pActor)
{
    m_ActorList.push_back(pActor);
}

void CLevel::Update()
{
    int NearDistance = 1600;
    for (auto& pSrc : m_JoinedSession)
    {
        for (auto& pDest : m_JoinedSession)
        {
            auto SrcInfo = pSrc->GetPlayer()->Get_Info();
            auto DestInfo = pDest->GetPlayer()->Get_Info();

            Vector3 vDis = DestInfo->Transform.vPosition - SrcInfo->Transform.vPosition;

            if (vDis.Get_SqrtLength() <= NearDistance)
            {
                pSrc->GetPlayer()->ADD_NearObject((HostID)pDest->Get_ID(), pDest->GetPlayer());
            }
            else
            {
                pSrc->GetPlayer()->Remove_NearObject((HostID)pDest->Get_ID(), pDest->GetPlayer());
            }
        }
    }


    Broadcast_Actor();
    Broadcast_Session();
}

bool CLevel::Get_Dead()
{
    return m_JoinedSession.empty();
}
