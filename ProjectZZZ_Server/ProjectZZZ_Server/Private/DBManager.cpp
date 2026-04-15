#include "pch.h"
#include "DBManager.h"

#include "ServerManager.h"
#include "Session.h"

CDBManager::CDBManager()
{
}

HRESULT CDBManager::Initialize()
{
    // 여기서 DB 연결 Test

    if (FAILED(Connection_Test()))
        return E_FAIL;

    if (FAILED(Excute_Test()))
        return E_FAIL;

    return S_OK;
}

HRESULT CDBManager::Connection_Test()
{
    Proud::String OpenDir =
        L"Driver={MySQL ODBC 9.6 Unicode Driver};"
        L"Server=127.0.0.1;"
        L"Port=3306;"
        L"Database=Item_Table;"
        L"Uid=root;"
        L"Pwd=chanbin@1013;"
        L"Option=3;";

    // 쿼리 에러를 담을 객체로 사용하지 않아도 무방합니다.
    COdbcWarnings       Warnings;
    try
    {
        m_Conn.Open(OpenDir, &Warnings);
        for (int i = 0; i < Warnings.Count; ++i)
            cout << Warnings[i].GetSqlErrorCode() << " : " << Warnings[i].what() << '\n';
        m_Conn.Close();
        m_Conn.Open(OpenDir, &Warnings);

    }
    catch (COdbcException& error)
    {
        cout << "Error : " << error.GetSqlErrorCode() << " => " << error.what() << '\n';
        return E_FAIL;
    }

    return S_OK;
}

HRESULT CDBManager::Excute_Test()
{
    int id, Level;
    Proud::String name;

    COdbcWarnings       Warnings;
    COdbcRecordset      record;       // 쿼리 결과를 담을 객체

    try
    {
        auto result = m_Conn.Execute(record, _PNT("SELECT * FROM player"), &Warnings);
        for (int i = 0; i < Warnings.Count; ++i)
            cout << Warnings[i].GetSqlErrorCode() << " : " << Warnings[i].what() << '\n';

        while (record.MoveNext())
        {
            id = record.GetFieldValue(_PNT("id"));
            name = record.GetFieldValue(_PNT("name"));
            Level = record.GetFieldValue(_PNT("level"));

            wprintf(L"ID : %d | Name : %s | Level : %d\n", id, name.GetString(), Level);
        }
    }
    catch (COdbcException& error)
    {
        cout << "Error : " << error.GetSqlErrorCode() << " => " << error.what() << '\n';
        return E_FAIL;
    }

    return S_OK;
}

void CDBManager::Release()
{
    m_Conn.Close();
}

bool CDBManager::Login_EXcuteDB(int ClientID, string ID, string Password)
{
    COdbcWarnings       Warnings;
    COdbcRecordset      record;       // 쿼리 결과를 담을 객체

    try
    {
        Proud::String Query = Proud::String::NewFormat(
            L"SELECT * FROM users WHERE User_ID = '%s' AND Password = '%s'",
            Proud::String(ID.c_str()).GetString(),
            Proud::String(Password.c_str()).GetString());
        
        auto result = m_Conn.Execute(record, Query, &Warnings);
        for (int i = 0; i < Warnings.Count; ++i)
            cout << Warnings[i].GetSqlErrorCode() << " : " << Warnings[i].what() << '\n';

        int Table_id;
        while (record.MoveNext())
        {
            Table_id = record.GetFieldValue(L"Table_id");
        }

        m_DBJobs.push(make_shared<USER_INFO>(ClientID, DB_TABLE_TYPE::REQUEST_ID, Table_id));
    }
    catch (COdbcException& error)
    {
        cout << "Error : " << error.GetSqlErrorCode() << " => " << error.what() << '\n';
        return false;
    }

    return true;
}

bool CDBManager::Request_UniqueNickName(int ClientID, string NickName)
{
    COdbcWarnings       Warnings;
    COdbcRecordset      record;       // 쿼리 결과를 담을 객체

    try
    {
        Proud::String Query = Proud::String::NewFormat(
            L"SELECT * FROM player WHERE nickname = '%s' LIMIT 1", NickName);

        auto result = m_Conn.Execute(record, Query, &Warnings);
        for (int i = 0; i < Warnings.Count; ++i)
            cout << Warnings[i].GetSqlErrorCode() << " : " << Warnings[i].what() << '\n';

        m_DBJobs.push(make_shared<DB_RESPONE_DATA>(ClientID, DB_TABLE_TYPE::REQUEST_NAME, record.MoveNext()));
    }
    catch (COdbcException& error)
    {
        cout << "Error : " << error.GetSqlErrorCode() << " => " << error.what() << '\n';
        return false;
    }

    return true;
}

bool CDBManager::RequestLoadPlayerData(int TableID, PLAYER_DATA& playerData)
{
    COdbcWarnings       Warnings;
    COdbcRecordset      record;       // 쿼리 결과를 담을 객체

    try
    {
        Proud::String Query = Proud::String::NewFormat(
            L"SELECT * FROM player WHERE id = '%d' LIMIT 1", TableID);

        auto result = m_Conn.Execute(record, Query, &Warnings);
        for (int i = 0; i < Warnings.Count; ++i)
            cout << Warnings[i].GetSqlErrorCode() << " : " << Warnings[i].what() << '\n';
    }
    catch (COdbcException& error)
    {
        cout << "Error : " << error.GetSqlErrorCode() << " => " << error.what() << '\n';
        return false;
    }

    return true;
}

void CDBManager::Update_DB(ServerToClient::Proxy* pProxy)
{
    while (!m_DBJobs.empty())
    {
        auto Data = m_DBJobs.front();
        m_DBJobs.pop();

        int ClientID = Data->ClientID;
        switch (Data->eType)
        {
        case DB_TABLE_TYPE::REQUEST_ID:
        {
            USER_INFO* pUserInfo = static_cast<USER_INFO*>(Data.get());
            CServerManager::Get_Instance()->ADD_JoinClient(CSession::Create(pUserInfo->ClientID, pUserInfo->TableID));

            cout << "LOG | Log In : SUCCESS" << endl;
            break;
        }
        case DB_TABLE_TYPE::REQUEST_NAME:
        {
            DB_RESPONE_DATA* pResponeData = static_cast<DB_RESPONE_DATA*>(Data.get());
            pProxy->ResponseCheckNickname((HostID)ClientID, RmiContext::ReliableSend, ClientID, pResponeData->bIsSuccess);
            break;
        }
        }
    }
}

CDBManager* CDBManager::Create()
{
    CDBManager* pInstance = new CDBManager();
    if (FAILED(pInstance->Initialize()))
    {
        delete pInstance;
        pInstance = nullptr;
    }

    return pInstance;
}
