#include "pch.h"
#include "Player.h"

CPlayer::CPlayer()
{

}

void CPlayer::Set_Info(const PLAYER_DATA* pinfo)
{
    m_pInfo = *pinfo;
}

void CPlayer::Set_Scale(float x, float y, float z)
{
    m_pInfo.Transform.vScale.X = x;
    m_pInfo.Transform.vScale.Y = y;
    m_pInfo.Transform.vScale.Z = z;
}

void CPlayer::Set_Rotation(float x, float y, float z, float w)
{
    m_pInfo.Transform.vRotation.X = x;
    m_pInfo.Transform.vRotation.Y = y;
    m_pInfo.Transform.vRotation.Z = z;
    m_pInfo.Transform.vRotation.W = w;
}

void CPlayer::Set_Poisition(float x, float y, float z)
{
    m_pInfo.Transform.vPosition.X = x;
    m_pInfo.Transform.vPosition.Y = y;
    m_pInfo.Transform.vPosition.Z = z;
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

    m_pInfo.Transform.vScale = Vector3::Zero;
    m_pInfo.Transform.vRotation = Vector4::Zero;
    m_pInfo.Transform.vPosition = Vector3::Zero;

    m_pInfo.bIsDead = false;
    m_AnimState = STATE_TYPE::END;

    return S_OK;
}
