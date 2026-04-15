#include "pch.h"
#include "Player.h"

CPlayer::CPlayer()
{

}

void CPlayer::Set_Info(const PLAYER_DATA* pinfo)
{
    m_pInfo = *pinfo;
}

void CPlayer::Set_Poisition(float x, float y, float z)
{
    m_pInfo.m_PosX = x;
    m_pInfo.m_PosY = y;
    m_pInfo.m_PosZ = z;
}

void CPlayer::Set_NickName(const string& szName)
{
    m_pInfo.Name = szName;
}

void CPlayer::Set_AnimSate(STATE_TYPE state, float fTime)
{
    m_AnimState = state;
    m_fAnimTime = 0.f;
}

void CPlayer::Set_Level(int iLevel)
{
    m_pInfo.Level = iLevel;
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
    m_pInfo.Level = 1;
    m_pInfo.Name = "";
    m_pInfo.m_PosX = m_pInfo.m_PosY = m_pInfo.m_PosZ = 0.f;
    m_pInfo.m_bIsDead = false;
    m_AnimState = STATE_TYPE::END;

    return S_OK;
}
