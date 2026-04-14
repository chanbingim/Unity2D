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

const Player_Data* CSession::Get_Info()
{
    if (m_pPlayer)
        return m_pPlayer->Get_Info();

    return nullptr;
}

CSession* CSession::Create(int HostID)
{
    CSession* pInstance = new CSession();
    if (FAILED(pInstance->Initialize(HostID)))
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

HRESULT CSession::Initialize(int HostID)
{
    m_pPlayer = CPlayer::Create();
    string NickName = "0" + m_hostID;

    m_pPlayer->Set_NickName(NickName);
    cout << "Join Player : " << m_pPlayer->Get_Info()->m_NickName << endl;

    return S_OK;
}
