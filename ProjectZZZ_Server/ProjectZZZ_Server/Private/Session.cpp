#include "pch.h"
#include "Session.h"

#include "Player.h"

void CSession::Set_Poisition(float x, float y, float z)
{
    if (m_pPlayer)
        m_pPlayer->Set_Poisition(x, y, z);
}

void CSession::Set_NickName(const string& szName)
{
    if (m_pPlayer)
        m_pPlayer->Set_NickName(szName);
}

void CSession::Set_MapID(int iMapID)
{
    m_EnterMapID = iMapID;
}

void CSession::Set_Level(int iLevel)
{
    if (m_pPlayer)
        m_pPlayer->Set_Level(iLevel);
}

void CSession::Set_Dead()
{
    if (m_pPlayer)
        m_pPlayer->Set_Dead();
}

void CSession::Set_AnimState(int iAnimState, float fTime)
{
    m_pPlayer->Set_AnimSate(CPlayer::STATE_TYPE(iAnimState), fTime);
}

void CSession::Set_Info(const PLAYER_DATA* pinfo)
{
    if (m_pPlayer)
        return m_pPlayer->Set_Info(pinfo);
}

const Player_Data* CSession::Get_Info()
{
    if (m_pPlayer)
        return m_pPlayer->Get_Info();

    return nullptr;
}

int CSession::Get_AnimSate()
{
    if (m_pPlayer)
        return static_cast<int>(m_pPlayer->Get_AnimSate());

    return -1;
}

float CSession::Get_AnimTime()
{
    if (m_pPlayer)
        return m_pPlayer->Get_AnimTime();

    return 0.f;
}

int CSession::Get_MapID()
{
    return m_EnterMapID;
}

shared_ptr<CSession> CSession::Create(int HostID, int TableID, PLAYER_DATA* info)
{
    shared_ptr<CSession> pInstance = make_shared<CSession>();
    if (FAILED(pInstance->Initialize(HostID, TableID, info)))
        pInstance = nullptr;

    return pInstance;
}

void CSession::Release()
{
    m_pPlayer->Release();
    delete m_pPlayer;
}

HRESULT CSession::Initialize(int HostID, int TableID, PLAYER_DATA* info)
{
    m_pPlayer = CPlayer::Create();
    m_hostID = HostID;
    m_TableID = TableID;

    if (nullptr == info)
    {
        string NickName = "Gesut : ";
        NickName += "0" + m_hostID;

        m_pPlayer->Set_NickName(NickName);
        cout << "Join Player : " << m_pPlayer->Get_Info()->szName << endl;
    }
    else
    {
        m_pPlayer->Set_Info(info);
        cout << "Join Player : " << m_pPlayer->Get_Info()->szName << endl;
    }

    return S_OK;
}
