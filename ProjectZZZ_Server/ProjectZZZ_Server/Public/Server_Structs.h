#pragma once
#pragma once
#include "Server_Defines.h"

#include "BasicTypes.h"
#include "OdbcWrap.h"



typedef struct Player_Data
{
    int iID;
    int iLevel;
    string szName;

    int iCurrentHP, iMaxHP;
    int iCurrentMP, iMaxMP;
    int iCurrentExp, iMaxExp;
    int iGlod;

    float       fPosX, fPosY, fPosZ;
    bool        bIsDead = false;
}PLAYER_DATA;

typedef struct Item_Data
{
    int ID;
    int Level;
    string Name;

    int CurrentHP, MaxHP;
    int CurrentMP, MaxMP;
}ITEM_DATA;

typedef struct Defualt_Error
{
    Defualt_Error(string errorMsg) : szErrorMsg(errorMsg) {}
    string      szErrorMsg;
}DEFUALT_ERROR;

typedef struct DB_Result
{
    DB_Result(int Id, DB_TABLE_TYPE Type) :
        ClientID(Id), eType(Type) {  }

    int                     ClientID;
    DB_TABLE_TYPE           eType;
}DB_RESULT;

typedef struct Login_Result : public DB_RESULT
{
    Login_Result(int Id, DB_TABLE_TYPE Type, int tableID, LOGIN_MSG  Msg) :
        DB_Result(Id, Type), TableID(tableID), Login_Msg(Msg) {}

    int         TableID;
    LOGIN_MSG   Login_Msg;

}LOGIN_RESULT;

typedef struct Login_Error : public DEFUALT_ERROR
{
    Login_Error(string ErrorMsg, LOGIN_MSG eLoginMsg) : DEFUALT_ERROR(ErrorMsg), eLoginMsg(eLoginMsg) {}
    LOGIN_MSG   eLoginMsg;
}LOGIN_ERROR;


typedef struct DB_Respone_Data : public DB_RESULT
{
     DB_Respone_Data(int Id, DB_TABLE_TYPE Type, int bSuccess) :
        DB_Result(Id, Type), bIsSuccess(bSuccess) {
    }

    bool bIsSuccess;
}DB_RESPONE_DATA;