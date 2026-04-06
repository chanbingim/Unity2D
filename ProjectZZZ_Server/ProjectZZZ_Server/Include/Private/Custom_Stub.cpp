#include "pch.h"
#include "Custom_Stub.h"
#include "ServerManager.h"

DEFRMI_ClientToServer_OnPositionUpdated(CCustom_Stub)
{
    cout << "Move Pos : " << PosX << PosY << PosZ << endl;

    float NewX = PosX + DirX;
    float NewY = PosY + DirY;
    float NewZ = PosZ + DirZ;

    auto pInstance = CServerManager::Get_Instance();
    Proxy* pProxy = pInstance->Get_Proxy();

    pInstance->Update_Player((HostID)clientId, NewX, NewY, NewZ);
    pProxy->OnPositionUpdated((HostID)clientId, RmiContext::UnreliableSend,
        clientId, NewX, NewY, NewZ, DirX, DirY, DirZ);

    return true;
}

DEFRMI_ClientToServer_OnChat(CCustom_Stub)
{

    return true;
}
