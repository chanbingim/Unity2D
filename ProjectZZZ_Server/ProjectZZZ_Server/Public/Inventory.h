#pragma once
#include "Server_Defines.h"

class CInventory
{
public :
    void                    ADD_Gold(int Amount);
    int                     ADD_Item(int ItemID, int ItemCount);

    bool                    Remove_Item(int SlotType, int ItemID, int ItemCount);
    //bool                  Remove_Item(int SlotType, int SlotIndex, int ItemCount);

    bool                    Swap_Data(int SlotType, int FromSlotIdx, int ToSlotIdx);

private :
    int                     m_Gold;

    int                     m_MaxSlotCount[EnumToInt(ITEM_TYPE::END)];
    int                     m_CurSlotCount[EnumToInt(ITEM_TYPE::END)];

    vector<ItemSlot>        m_Slots[EnumToInt(ITEM_TYPE::END)];
    priority_queue<int>     m_FreeSlotIndices[EnumToInt(ITEM_TYPE::END)];

public :
    static  shared_ptr<CInventory>     Create();

private :
    HRESULT                             Initialize();

};

