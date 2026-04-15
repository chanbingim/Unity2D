#pragma once
#pragma once
#include "Server_Defines.h"

#include "BasicTypes.h"
#include "OdbcWrap.h"

enum DB_TABLE_TYPE { REQUEST_ID, REQUEST_NAME, PLAYER, ITEM, END };

typedef struct Player_Data
{
    int ID;
    int Level;
    string Name;

    int CurrentHP, MaxHP;
    int CurrentMP, MaxMP;

    float       m_PosX, m_PosY, m_PosZ;
    bool        m_bIsDead = false;
}PLAYER_DATA;

typedef struct Item_Data
{
    int ID;
    int Level;
    string Name;

    int CurrentHP, MaxHP;
    int CurrentMP, MaxMP;
}ITEM_DATA;

typedef struct DB_Result
{
    DB_Result(int Id, DB_TABLE_TYPE Type) :
        ClientID(Id), eType(Type) {  }

    int                     ClientID;
    DB_TABLE_TYPE           eType;
}DB_RESULT;


typedef struct UserInfo : public DB_RESULT
{
    UserInfo(int Id, DB_TABLE_TYPE Type, int tableID) : 
        DB_Result(Id, Type), TableID(tableID) {}

    int TableID;
}USER_INFO;

typedef struct DB_Respone_Data : public DB_RESULT
{
     DB_Respone_Data(int Id, DB_TABLE_TYPE Type, int bSuccess) :
        DB_Result(Id, Type), bIsSuccess(bSuccess) {
    }

    bool bIsSuccess;
}DB_RESPONE_DATA;