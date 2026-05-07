#pragma once
#pragma once
#include "Server_Defines.h"

#include "BasicTypes.h"
#include "OdbcWrap.h"

struct Transform
{
    Transform() : vScale(Vector3::Zero), vRotation(Vector4::Zero), vPosition(Vector3::Zero) {}
    Transform(Vector3 Scale) : vScale(Scale), vRotation(Vector4::Zero), vPosition(Vector3::Zero) {}
    Transform(Vector3 Scale, Vector4 Rotation) : vScale(Scale), vRotation(Rotation), vPosition(Vector3::Zero) {}

    Transform(Vector3 Scale, Vector4 Rotation, Vector3 Pos) :
        vScale(Scale), vRotation(Rotation), vPosition(Pos) {}
    
    Vector3     vScale;
    Vector4     vRotation;
    Vector3     vPosition;

};

typedef struct Player_Data
{
    int iID;
    int iLevel;
    string szName;

    int iCurrentHP, iMaxHP;
    int iCurrentMP, iMaxMP;
    int iCurrentExp, iMaxExp;
    int iGlod;

    Transform   Transform;
    bool        bIsDead = false;
}PLAYER_DATA;

struct ItemSlot
{
    int iSlotIndex;
    int iItemCount;
    int iItemID;
};

typedef struct Item_Data
{
    int         ID;
    string      Name;

    int         MaxCount;
    int         ItemType;

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

typedef struct Create_Id_Result : public DB_RESULT
{
    Create_Id_Result(int Id, DB_TABLE_TYPE Type, CREATEID_MSG  Msg) :
        DB_Result(Id, Type), eMsg(Msg) {
    }

    CREATEID_MSG    eMsg;

}CREATE_ID_RESULT;

typedef struct DB_Respone_Data : public DB_RESULT
{
     DB_Respone_Data(int Id, DB_TABLE_TYPE Type, int bSuccess) :
        DB_Result(Id, Type), bIsSuccess(bSuccess) {
    }

    bool bIsSuccess;
}DB_RESPONE_DATA;