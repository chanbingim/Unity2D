#pragma once
#include "Server_Defines.h"

class CInventory
{
public :
    void                    ADD_Gold(int Amount);
    int                     ADD_Item(const Item_Data& Data, int ItemCount);

    //bool                  Remove_Item(int SlotType, int ItemID, int ItemCount);
    bool                    Remove_Item(int SlotType, int SlotIndex, int ItemCount);

    bool                    Swap_Data(int SlotType, int FromSlotIdx, int ToSlotIdx);
    const vector<ItemSlot>& Get_Items(int SlotType) { return m_Slots[SlotType]; }

    void                    Update(int ihostID);

private :
    queue<pair<int, int>>   m_UpdateSlots;
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

