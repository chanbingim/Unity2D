#pragma once

enum class LOGIN_MSG { SUCCESS, ID_FAIL, PW_FAIL, END };

enum class CREATEID_MSG { SAME_ID, SUCCESS, END };
enum class ITEM_TYPE  { EQUIP, CONSUME, ETC, END };

enum class DB_TABLE_TYPE { REQUEST_ID, 
                           CREATE_ID,
                           REQUEST_NAME,
                           PLAYER,
                           ITEM,
                           END };