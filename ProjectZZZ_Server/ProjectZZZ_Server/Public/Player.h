#pragma once
#include "Actor.h"

class CInventory;

class CPlayer : public CActor
{
public :
    enum class STATE_TYPE {
        IDLE = 0, WALK, RUN, ATTACK, DEAD, END
    };

public:
    const PLAYER_DATA*      Get_Info() { return &m_pInfo; }
    const STATE_TYPE&       Get_AnimSate() { return m_AnimState; }
    float                   Get_AnimTime() { return m_fAnimTime; }

    void                    Set_Info(const PLAYER_DATA* pinfo);

    // Transform
    void                    Set_Scale(float x, float y, float z);
    void                    Set_Rotation(float x, float y, float z, float w);
    void                    Set_Poisition(float x, float y, float z);

    void                    Set_NickName(const string& szName);
    void                    Set_AnimSate(STATE_TYPE state, float fTime = 0.f);
    void                    Set_Level(int iLevel);
    void                    Set_Dead();
    
#pragma region Inventory
    void                    ADD_Gold(int Amount);
    int                     Picked_Item(int ItemID, int ItemCount);
#pragma endregion

    void                        ADD_NearObject(HostID iHostID, CActor* pActor);
    void                        Remove_NearObject(HostID iHostID, CActor* pActor);

    HostID*                     Get_HostList();
    size_t                      Get_Hosts() { return m_NearHostID.size(); }

private:
    PLAYER_DATA                 m_pInfo;
    STATE_TYPE                  m_AnimState = STATE_TYPE::END;
    float                       m_fAnimTime = 0.f;

    vector<HostID>              m_NearHostID;
    vector<CActor*>             m_NearVisible;

    shared_ptr<CInventory>      m_pInventory = nullptr;

public :
    static unique_ptr<CPlayer>  Create();
    void                        Release();

private :
    HRESULT                 Initialize();

};

