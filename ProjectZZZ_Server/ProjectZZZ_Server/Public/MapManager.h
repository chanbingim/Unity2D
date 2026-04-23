#pragma once
#include "Base.h"

class CLevel;

class CMapManager : public CBase
{
public :
    void                    Update();

    void                    Join_Level(shared_ptr<class CSession> pSession, int LevelID);
    void                    Leave_Level(shared_ptr<class CSession> pSession, int LevelID);

private :
    unordered_map<int, shared_ptr<CLevel>>      m_MapList;
    vector<shared_ptr<CLevel>>                  m_LevelList;

private :
    HRESULT                 Initialize();

public :
    static shared_ptr<CMapManager>      Create();
    virtual void                        Release();

};

