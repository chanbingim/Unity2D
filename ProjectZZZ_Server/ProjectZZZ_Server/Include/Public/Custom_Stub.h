#pragma once
#include "ClientRmi_stub.h"

using namespace ClientToServer;

class CCustom_Stub : public Stub
{
public :
    // Stub
    DECRMI_ClientToServer_OnPositionUpdated;
    DECRMI_ClientToServer_OnChat;

};

