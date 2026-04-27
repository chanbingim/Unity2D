#include "pch.h"
#include "DBManager.h"

#include "ServerManager.h"
#include "Session.h"

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
        L"Database=User_DB;"
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
    COdbcWarnings       Warnings;
    COdbcRecordset      record;       // 쿼리 결과를 담을 객체

    try
    {
        auto result = m_Conn.Execute(record, _PNT("SELECT * FROM player_info"), &Warnings);
        for (int i = 0; i < Warnings.Count; ++i)
            cout << Warnings[i].GetSqlErrorCode() << " : " << Warnings[i].what() << '\n';

        while (record.MoveNext())
        {
           
        }
    }
    catch (COdbcException& error)
    {
        cout << "Error : " << error.GetSqlErrorCode() << " => " << error.what() << '\n';
        return E_FAIL;
    }

    return S_OK;
}

#pragma region Login
int CDBManager::Request_LoginID(const string& ID)
{
    COdbcWarnings       Warnings;
    COdbcRecordset      record;       // 쿼리 결과를 담을 객체

    try
    {
        Proud::String Query = Proud::String::NewFormat(
            L"SELECT id FROM users WHERE user_id = '%s'",
            Proud::String(ID.c_str()).GetString());

        auto result = m_Conn.Execute(record, Query, &Warnings);
        for (int i = 0; i < Warnings.Count; ++i)
            cout << Warnings[i].GetSqlErrorCode() << " : " << Warnings[i].what() << '\n';

        int TableId(0);
        while (record.MoveNext())
        {
            TableId = record.GetFieldValue(_PNT("id"));
        }

        return TableId;
    }
    catch (COdbcException& error)
    {
        cout << "Error : " << error.GetSqlErrorCode() << " => " << error.what() << '\n';
        return false;
    }

    return false;
}

bool CDBManager::Request_LoginPassWord(const string& Pw)
{
    COdbcWarnings       Warnings;
    COdbcRecordset      record;       // 쿼리 결과를 담을 객체

    try
    {
        string Query = Proud::String::NewFormat(
            L"SELECT password FROM users WHERE password = '%s'",
            Proud::String(Pw.c_str()).GetString());

        auto result = m_Conn.Execute(record, Query, &Warnings);
        for (int i = 0; i < Warnings.Count; ++i)
            cout << Warnings[i].GetSqlErrorCode() << " : " << Warnings[i].what() << '\n';

        return 0 == record.GetRowCount() ? false : true;
    }
    catch (COdbcException& error)
    {
        cout << "Error : " << error.GetSqlErrorCode() << " => " << error.what() << '\n';
        return false;
    }

    return false;
}
#pragma endregion

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
		int Table_id(-1);

#pragma region ID_CHECK
        if (!Request_LoginID(ID))
        {
            m_DBJobs.push(make_shared<LOGIN_RESULT>(ClientID, DB_TABLE_TYPE::REQUEST_ID, Table_id, LOGIN_MSG::ID_FAIL));
            return false;
        }
#pragma endregion

#pragma region PW_CHECK
        if (!Request_LoginPassWord(Password))
        {
            m_DBJobs.push(make_shared<LOGIN_RESULT>(ClientID, DB_TABLE_TYPE::REQUEST_ID, Table_id, LOGIN_MSG::PW_FAIL));
            return false;
        }
#pragma endregion

		m_DBJobs.push(make_shared<LOGIN_RESULT>(ClientID, DB_TABLE_TYPE::REQUEST_ID, Table_id, LOGIN_MSG::SUCCESS));

	}
    catch (COdbcException& error)
    {
        cout << "Error : " << error.GetSqlErrorCode() << " => " << error.what() << '\n';
        return false;
    }

    return true;
}

void CDBManager::Insert_NewID(int ClientID, string ID, string Password, string Email)
{
    COdbcWarnings       Warnings;
    COdbcRecordset      record;       // 쿼리 결과를 담을 객체

    try
    {
        int Table_id(-1);

        if (Request_LoginID(ID))
            m_DBJobs.push(make_shared<CREATE_ID_RESULT>(ClientID, DB_TABLE_TYPE::CREATE_ID, CREATEID_MSG::SAME_ID));
        else
        {
            Proud::String Query = Proud::String::NewFormat(
                L"Insert INTO users(user_id, password, email) VALUES"
                L"(%s, %s, alice@gmail.com)", ID, Password);

            auto result = m_Conn.Execute(record, Query, &Warnings);
        }
    }
    catch (COdbcException& error)
    {
        cout << "Error : " << error.GetSqlErrorCode() << " => " << error.what() << '\n';
    }
}

bool CDBManager::Request_UniqueNickName(int ClientID, string NickName)
{
    COdbcWarnings       Warnings;
    COdbcRecordset      record;       // 쿼리 결과를 담을 객체

    try
    {
        Proud::String Query = Proud::String::NewFormat(
            L"SELECT * FROM player_info WHERE nickname = '%s' LIMIT 1", NickName);

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

    Proud::String  NickName;
    try
    {
        Proud::String Query = Proud::String::NewFormat(
            L"SELECT * FROM player_info WHERE id = '%d' LIMIT 1", TableID);

        auto result = m_Conn.Execute(record, Query, &Warnings);
        while (record.MoveNext())
        {
            playerData.iID = record.GetFieldValue(_PNT("user_id"));
            NickName = record.GetFieldValue(_PNT("nickname"));
            playerData.szName = string(NickName);

            playerData.iLevel = record.GetFieldValue(_PNT("level"));
            playerData.iMaxExp = record.GetFieldValue(_PNT("exp"));

            playerData.iMaxHP = record.GetFieldValue(_PNT("hp"));
            playerData.iMaxMP = record.GetFieldValue(_PNT("mp"));
            playerData.iGlod = record.GetFieldValue(_PNT("Gold"));

            playerData.fPosX = record.GetFieldValue(_PNT("pos_x"));
            playerData.fPosY = record.GetFieldValue(_PNT("pos_y"));
            playerData.fPosZ = record.GetFieldValue(_PNT("pos_z"));

#pragma region print_Log
            wprintf(L"-------------Find Success-------------\n");
            wprintf(L"ID : %d\n", playerData.iID);
            wprintf(L"NickName : %s\n", playerData.szName.c_str());
            wprintf(L"Level : %d\n", playerData.iLevel);
            wprintf(L"Exp : %d\n", playerData.iMaxExp);
            wprintf(L"HP : %d\n", playerData.iMaxHP);
            wprintf(L"MP : %d\n", playerData.iMaxMP);
            wprintf(L"Gold : %d\n", playerData.iGlod);
            wprintf(L"Position : %f, %f, %f \n", playerData.fPosX, playerData.fPosY, playerData.fPosZ);
            wprintf(L"-----------------------------------\n");
#pragma endregion
        }

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
			LOGIN_RESULT* pUserInfo = static_cast<LOGIN_RESULT*>(Data.get());
			if (LOGIN_MSG::SUCCESS == pUserInfo->Login_Msg)
			{
				CServerManager::Get_Instance()->ADD_JoinClient(pUserInfo->ClientID, CSession::Create(pUserInfo->ClientID, pUserInfo->TableID), pUserInfo->Login_Msg);
				cout << "LOG | Log In : SUCCESS" << endl;
			}
			else
				CServerManager::Get_Instance()->ADD_JoinClient(pUserInfo->ClientID, nullptr, pUserInfo->Login_Msg);

          
            break;
        }
        case DB_TABLE_TYPE::REQUEST_NAME:
        {
            DB_RESPONE_DATA* pResponeData = static_cast<DB_RESPONE_DATA*>(Data.get());
            pProxy->ResponseCheckNickname((HostID)ClientID, RmiContext::ReliableSend, ClientID, pResponeData->bIsSuccess);
            break;
        }
        case DB_TABLE_TYPE::CREATE_ID:
        {
            CREATE_ID_RESULT* pCreateIDData = static_cast<CREATE_ID_RESULT*>(Data.get());
            if (CREATEID_MSG::SUCCESS != pCreateIDData->eMsg)
                //pProxy->ResponseCheckNickname((HostID)ClientID, RmiContext::ReliableSend, ClientID, pResponeData->bIsSuccess);
            break;
        }
        }
    }
}

bool CDBManager::SavePlayerData(int TableID, PLAYER_DATA& playerData)
{
    return false;
}

shared_ptr<CDBManager>  CDBManager::Create()
{
    shared_ptr<CDBManager> pInstance = make_shared<CDBManager>();
    if (FAILED(pInstance->Initialize()))
        pInstance = nullptr;

    return pInstance;
}
