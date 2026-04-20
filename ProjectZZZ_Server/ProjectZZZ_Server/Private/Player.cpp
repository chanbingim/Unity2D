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
    m_pInfo.fPosX = x;
    m_pInfo.fPosY = y;
    m_pInfo.fPosZ = z;
}

void CPlayer::Set_NickName(const string& szName)
{
    m_pInfo.szName = szName;
}

void CPlayer::Set_AnimSate(STATE_TYPE state, float fTime)
{
    m_AnimState = state;
    m_fAnimTime = 0.f;
}

void CPlayer::Set_Level(int iLevel)
{
    m_pInfo.iLevel = iLevel;
}

void CPlayer::Set_Dead()
{
    m_pInfo.bIsDead = true;
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
    m_pInfo.iLevel = 1;
    m_pInfo.szName = "";
    m_pInfo.fPosX = m_pInfo.fPosY = m_pInfo.fPosZ = 0.f;
    m_pInfo.bIsDead = false;
    m_AnimState = STATE_TYPE::END;

    return S_OK;
}
