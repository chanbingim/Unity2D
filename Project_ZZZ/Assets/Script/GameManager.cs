using System;
using UnityEngine;
using UnityEngine.Assertions.Must;

public class GameManager : MonoBehaviour
{
    static GameManager              m_pInstance = null;
    CUtilyManager                   m_gUtilyMgr = null;
    CInputManager                   m_pInputManager = null;

    public static GameManager GetInstance() { return m_pInstance; }
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Awake()
    {
        if(null == m_pInstance)
        {
            m_pInstance = this;
            m_gUtilyMgr = CUtilyManager.Get_Instance();
            m_pInputManager = CInputManager.Create();

            GameClient.Get_Instance();
            Debug.Log("Create Manager");
        }
        else
            Destroy(m_pInstance);
    }

    // Update is called once per frame
    void Update()
    {
        m_pInputManager.Update();
    }

    public void Add_ListenList(Action<Boolean> Event)
    {
        m_pInputManager.EnableChating += Event;
    }

}
