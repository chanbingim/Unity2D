#pragma once
#include "ClientRmi_stub.h"

using namespace ClientToServer;

class CServerManager;

class CCustom_Stub : public Stub
{
private:
    CCustom_Stub() = default;
    ~CCustom_Stub() = default;

public:
    // Stub
    DECRMI_ClientToServer_OnGameLogin;
    DECRMI_ClientToServer_SpawnPlayerEvent;
    DECRMI_ClientToServer_SpawnObjectEvent;

    DECRMI_ClientToServer_Create_Character;
    DECRMI_ClientToServer_RequestCheckNickname;

    DECRMI_ClientToServer_OnPositionUpdated;
    DECRMI_ClientToServer_OnAnimUpdated;
    DECRMI_ClientToServer_OnChat;

    DECRMI_ClientToServer_OnActorPositionUpdated;
    DECRMI_ClientToServer_OnActorAnimUpdated;
 
    DECRMI_ClientToServer_Request_AddItem;
    DECRMI_ClientToServer_Request_AddGold;
    DECRMI_ClientToServer_Request_RemoveItem;
    DECRMI_ClientToServer_Request_ItemData;

public:
    static  CCustom_Stub*       Create();
    void                        Release();

private:
    HRESULT                     Initialize();

private:
    CServerManager*             m_pInstance = nullptr;
};