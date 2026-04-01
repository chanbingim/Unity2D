#pragma once

class CCustom_Stub;
class CServer_Event;

using namespace ServerToClient;

class CServerManager
{
private :
    CServerManager();
    ~CServerManager();

public :
    static  CServerManager* Get_Instance(ErrorInfoPtr Error);
    static  CServerManager* Get_Instance();

    Proxy*              Get_Proxy()     { return m_pProxy; }

private :
    void                    Initalized(ErrorInfoPtr Error);

private :
    static CServerManager*  m_pGameInstance;

    Proxy*                  m_pProxy = nullptr;
    CCustom_Stub*           m_pStub = nullptr;
    CNetServer*             m_pServer = nullptr;
    CServer_Event*          m_pEvent = nullptr;
};

