#include "pch.h"
#include "Player.h"

#include "Inventory.h"
#include "ServerManager.h"

void CPlayer::Set_Info(const PLAYER_DATA* pinfo)
{
    m_pInfo = *pinfo;
}

void CPlayer::Set_Scale(float x, float y, float z)
{
    m_pInfo.Transform.vScale.X = x;
    m_pInfo.Transform.vScale.Y = y;
    m_pInfo.Transform.vScale.Z = z;
}

void CPlayer::Set_Rotation(float x, float y, float z, float w)
{
    m_pInfo.Transform.vRotation.X = x;
    m_pInfo.Transform.vRotation.Y = y;
    m_pInfo.Transform.vRotation.Z = z;
    m_pInfo.Transform.vRotation.W = w;
}

void CPlayer::Set_Poisition(float x, float y, float z)
{
    m_pInfo.Transform.vPosition.X = x;
    m_pInfo.Transform.vPosition.Y = y;
    m_pInfo.Transform.vPosition.Z = z;
}

void CPlayer::Set_NickName(const string& szName)
{
    m_pInfo.szName = szName;
}

void CPlayer::Set_AnimSate(STATE_TYPE state, float fTime)
{
    m_AnimState = state;
    m_fAnimTime = 0.f;
}

void CPlayer::Set_Level(int iLevel)
{
    m_pInfo.iLevel = iLevel;
}

void CPlayer::Set_Dead()
{
    m_pInfo.bIsDead = true;
}

void CPlayer::Inveontory_Update(int ihostID)
{
    m_pInventory->Update(ihostID);
}

void CPlayer::ADD_Gold(int Amount)
{
    if (nullptr == m_pInventory)
        return;

    m_pInventory->ADD_Gold(Amount);
}

int CPlayer::Get_Gold()
{
    return m_pInventory->Get_Gold();
}

int CPlayer::Picked_Item(const ITEM_DATA& Data, int ItemCount)
{
    if (nullptr == m_pInventory)
        return -1;

    return m_pInventory->ADD_Item(Data, ItemCount);
}

bool CPlayer::Remove_Item(const ITEM_DATA& Data, int SlotIndex, int ItemCount)
{
    if (nullptr == m_pInventory)
        return false;

    return m_pInventory->Remove_Item(Data.ItemType, SlotIndex, ItemCount);
}

const vector<ItemSlot>& CPlayer::Get_InventoryItems(int SlotType)
{
    return m_pInventory->Get_Items(SlotType);
}

void CPlayer::ADD_NearObject(HostID iHostID, CActor* pActor)
{
    auto iter = find(m_NearHostID.begin(), m_NearHostID.end(), iHostID);
    if (iter == m_NearHostID.end())
        m_NearHostID.push_back(iHostID);
}

void CPlayer::Remove_NearObject(HostID iHostID, CActor* pActor)
{
    int iNumActors = m_NearHostID.size();
    for (int i = 0; i < iNumActors; ++i)
    {
        if (iHostID == m_NearHostID[i])
        {
            m_NearHostID[i] = m_NearHostID.back();
            m_NearHostID.pop_back();
            return;
        }
    }
}

HostID* CPlayer::Get_HostList()
{
    if (m_NearHostID.empty())
        return nullptr;

    return m_NearHostID.data();
}

unique_ptr<CPlayer> CPlayer::Create()
{
    unique_ptr<CPlayer> pInstance = make_unique<CPlayer>();
    if (FAILED(pInstance->Initialize()))
    {
        return nullptr;
    }

    return pInstance;
}

void CPlayer::Release()
{
   
}

HRESULT CPlayer::Initialize()
{
    m_pInfo.iLevel = 1;
    m_pInfo.szName = "";

    m_pInfo.Transform.vScale = Vector3::One;
    m_pInfo.Transform.vRotation = Vector4::Zero;
    m_pInfo.Transform.vPosition = Vector3::Zero;

    m_pInfo.bIsDead = false;
    m_AnimState = STATE_TYPE::END;

    m_pInventory = CInventory::Create();

    return S_OK;
}
