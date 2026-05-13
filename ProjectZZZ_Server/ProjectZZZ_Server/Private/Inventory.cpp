#include "pch.h"
#include "Inventory.h"

shared_ptr<CInventory> CInventory::Create()
{
    shared_ptr<CInventory> pInstance = make_shared<CInventory>();
    if (FAILED(pInstance->Initialize()))
        pInstance = nullptr;

    return pInstance;
}

HRESULT CInventory::Initialize()
{

    return S_OK;
}

void CInventory::ADD_Gold(int Amount)
{
    m_Gold += Amount;
}

int CInventory::ADD_Item(int ItemID, int ItemCount)
{
    Item_Data Data;

    for (auto& slot : m_Slots[Data.ItemType])
    {
        if (0 == slot.iItemID)
            continue;

        if (slot.iItemID == ItemID)
        {
            int AddCount = min(Data.MaxCount - slot.iItemCount, ItemCount);
            slot.iItemCount += AddCount;
            ItemCount -= AddCount;
        }
    }

    if (m_FreeSlotIndices[Data.ItemType].empty())
        return ItemCount;

    while (!m_FreeSlotIndices[Data.ItemType].empty())
    {
        int FreeIndex = m_FreeSlotIndices[Data.ItemType].top();
        m_FreeSlotIndices[Data.ItemType].pop();

        int AddCount = min(Data.MaxCount, ItemCount);
        m_Slots[Data.ItemType][FreeIndex].iItemID = ItemID;
        m_Slots[Data.ItemType][FreeIndex].iItemCount = AddCount;

        ItemCount -= AddCount;
    }

    return ItemCount;
}

//bool CInventory::Remove_Item(int SlotType, int ItemID, int ItemCount)
//{
//    for (auto& slot : m_Slots[SlotType])
//    {
//        if (0 == slot.iItemID)
//            continue;
//
//        if (0 >= ItemCount)
//            break;
//
//        if (slot.iItemID == ItemID)
//        {
//            slot.iItemCount -= ItemCount;
//            if (0 > slot.iItemCount)
//            {
//                ItemCount = slot.iItemCount * -1;
//                slot.iItemCount = 0;
//            }
//        }
//    }
//
//    return 0 >= ItemCount ? false : true;
//}

bool CInventory::Remove_Item(int SlotType, int SlotIndex, int ItemCount)
{
    auto slot = m_Slots[SlotType][SlotIndex];
    if (0 == slot.iItemID)
        return false;;

    if (SlotIndex < 0 || m_MaxSlotCount[SlotType] <= SlotIndex)
    {
        cout << "[Inventory] Slot Out Bound" << endl;
        return false;
    }

    if (slot.iItemCount < ItemCount)
    {
        cout << "[Inventory] 아이템 버리기 Fail" << endl;
        return false;
    }

    slot.iItemCount -= ItemCount;
    if (0 >= slot.iItemCount)
    {
        slot.iItemID = 0;
        slot.iItemCount = 0;
    }
    return true;
}

bool CInventory::Swap_Data(int SlotType, int FromSlotIdx, int ToSlotIdx)
{
    if (FromSlotIdx < 0 || m_MaxSlotCount[SlotType] <= FromSlotIdx ||
        ToSlotIdx < 0 || m_MaxSlotCount[SlotType] <= ToSlotIdx)
    {
        cout << "[Inventory] Slot Out Bound" << endl;
        return false;
    }

    ItemSlot Temp = m_Slots[SlotType][FromSlotIdx];
    m_Slots[SlotType][FromSlotIdx].iItemID = m_Slots[SlotType][ToSlotIdx].iItemID;
    m_Slots[SlotType][FromSlotIdx].iItemCount = m_Slots[SlotType][ToSlotIdx].iItemCount;

    m_Slots[SlotType][ToSlotIdx].iItemID = Temp.iItemID;
    m_Slots[SlotType][ToSlotIdx].iItemCount = Temp.iItemCount;

    return true;
}