#include "pch.h"
#include "Session.h"
#include "Player.h"

CSession::CSession()
{

}

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

CSession* CSession::Create(int HostID, int TableID, PLAYER_DATA* info)
{
    CSession* pInstance = new CSession();
    if (FAILED(pInstance->Initialize(HostID, TableID, info)))
    {
        delete pInstance;
        pInstance = nullptr;
    }

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
        cout << "Join Player : " << m_pPlayer->Get_Info()->Name << endl;
    }
    else
    {
        m_pPlayer->Set_Info(info);
        cout << "Join Player : " << m_pPlayer->Get_Info()->Name << endl;
    }

    return S_OK;
}
