#include "pch.h"
#include "Custom_Stub.h"
#include "ServerManager.h"

DEFRMI_ClientToServer_OnPositionUpdated(CCustom_Stub)
{
    cout << "Move Pos : " << PosX << PosY << PosZ << endl;

    float NewX = PosX + DirX;
    float NewY = PosY + DirY;
    float NewZ = PosZ + DirZ;

    Proxy* pProxy = CServerManager::Get_Instance()->Get_Proxy();
    pProxy->OnPositionUpdated((HostID)clientId, RmiContext::UnreliableSend,
        clientId, NewX, NewY, NewZ, DirX, DirY, DirZ);

    return true;
}

DEFRMI_ClientToServer_OnChat(CCustom_Stub)
{

    return true;
}
