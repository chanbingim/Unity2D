#pragma once
#include "Base.h"

class CDBManager : public CBase
{
public :
    bool                    Login_EXcuteDB(int ClientID, string ID, string Password);
    bool                    Request_UniqueNickName(int ClientID, string NickName);
    bool                    RequestLoadPlayerData(int TableID, PLAYER_DATA& playerData);

    void                    Update_DB(ServerToClient::Proxy* pProxy);

private :
    COdbcConnection                 m_Conn;
    COdbcCommand                    m_cmd;          // 명령을 설정할 객체
    queue<shared_ptr<DB_RESULT>>    m_DBJobs;

public :
    static shared_ptr<CDBManager>       Create();
    virtual void                        Release();

private :
    HRESULT                 Initialize();

    // DB 연결 Test
    HRESULT                 Connection_Test();

    // DB 데이터 가져오기 Test
    HRESULT                 Excute_Test();

};

