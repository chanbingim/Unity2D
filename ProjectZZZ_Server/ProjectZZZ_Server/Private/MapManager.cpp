#include "pch.h"
#include "MapManager.h"

#include "Level.h"
#include "Session.h"

void CMapManager::Update()
{
    for (auto level = m_LevelList.begin(); level != m_LevelList.end();)
    {
        if ((*level)->Get_Dead())
            level = m_LevelList.erase(level);
        else
            (*level)->Update();
    }
}

void CMapManager::Join_Level(shared_ptr<class CSession> pSession,  int LevelID)
{
    shared_ptr<CLevel> plevel = nullptr;
    auto iter = m_MapList.find(LevelID);
    if (iter == m_MapList.end())
    {
        plevel = CLevel::Create(LevelID);
        m_MapList.emplace(LevelID, plevel);
        m_LevelList.push_back(plevel);
    }
    else
        plevel = iter->second;

    pSession->Set_MapID(LevelID);
    plevel->Join_Session(pSession);
}

void CMapManager::Leave_Level(shared_ptr<class CSession> pSession, int LevelID)
{
    pSession->Set_MapID(LevelID);
}

HRESULT CMapManager::Initialize()
{
    m_MapList.reserve(100);
    return S_OK;
}

shared_ptr<CMapManager> CMapManager::Create()
{
    shared_ptr<CMapManager> pInstance = make_shared<CMapManager>();
    if (FAILED(pInstance->Initialize()))
        pInstance = nullptr;

    return pInstance;
}

void CMapManager::Release()
{
    for (auto& iter : m_MapList)
        iter.second->Release();

    m_MapList.clear();
}
