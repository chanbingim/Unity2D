#include "pch.h"
#include "Custom_Stub.h"
#include "ServerManager.h"

DEFRMI_ClientToServer_OnPositionUpdated(CCustom_Stub)
{
    cout << "Move Pos : " << PosX << PosY << PosZ << endl;

    float NewX = PosX + DirX;
    float NewY = PosY + DirY;
    float NewZ = PosZ + DirZ;

    m_pInstance->Update_Player((HostID)clientId, NewX, NewY, NewZ);
    return true;
}

DEFRMI_ClientToServer_OnChat(CCustom_Stub)
{
    m_pInstance->ADD_Chat((HostID)clientId, message);
    return true;
}

DEFRMI_ClientToServer_OnGameLogin(CCustom_Stub)
{
    m_pInstance->Login_EXcuteDB(clientId, szID, szPassWord);
    return true;
}

DEFRMI_ClientToServer_OnAnimUpdated(CCustom_Stub)
{

    return true;
}

DEFRMI_ClientToServer_RequestCheckNickname(CCustom_Stub)
{
    m_pInstance->Request_UniqueNickName(clientId, szNickName);
    return true;
}

DEFRMI_ClientToServer_Create_Character(CCustom_Stub)
{
    //m_pInstance->Get_ExcuteDB();
    return true;
}


CCustom_Stub* CCustom_Stub::Create()
{
    CCustom_Stub* pInstance = new CCustom_Stub();
    if (FAILED(pInstance->Initialize()))
    {
        delete pInstance;
        pInstance = nullptr;
    }

    return pInstance;
}

void CCustom_Stub::Release()
{

}

HRESULT CCustom_Stub::Initialize()
{
    m_pInstance = CServerManager::Get_Instance();

    return S_OK;
}
