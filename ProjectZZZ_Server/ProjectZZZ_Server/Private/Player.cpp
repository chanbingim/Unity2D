#include "pch.h"
#include "Player.h"

CPlayer::CPlayer()
{

}

void CPlayer::Set_Poisition(float x, float y, float z)
{
    m_pInfo.m_PosX = x;
    m_pInfo.m_PosY = y;
    m_pInfo.m_PosZ = z;
}

void CPlayer::Set_NickName(const string& szName)
{
    m_pInfo.m_NickName = szName;
}

void CPlayer::Set_Level(int iLevel)
{
    m_pInfo.m_iLevel = iLevel;
}

void CPlayer::Set_Dead()
{
    m_pInfo.m_bIsDead = true;
}

CPlayer* CPlayer::Create()
{
    CPlayer* pInstance = new CPlayer();
    if (FAILED(pInstance->Initialize()))
    {
        delete pInstance;
        pInstance = nullptr;
    }

    return pInstance;
}

void CPlayer::Release()
{
   
}

HRESULT CPlayer::Initialize()
{
    m_pInfo.m_iLevel = 1;
    m_pInfo.m_NickName = "";
    m_pInfo.m_PosX = m_pInfo.m_PosY = m_pInfo.m_PosZ = 0.f;
    m_pInfo.m_bIsDead = false;
    m_AnimState = STATE_TYPE::END;

    return S_OK;
}
