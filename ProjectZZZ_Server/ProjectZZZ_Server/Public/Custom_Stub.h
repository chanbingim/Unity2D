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
    DECRMI_ClientToServer_Create_Character;
    DECRMI_ClientToServer_RequestCheckNickname;

    DECRMI_ClientToServer_OnPositionUpdated;
    DECRMI_ClientToServer_OnAnimUpdated;
    DECRMI_ClientToServer_OnChat;
 
public:
    static  CCustom_Stub*       Create();
    void                        Release();

private:
    HRESULT                     Initialize();

private:
    CServerManager*             m_pInstance = nullptr;
};