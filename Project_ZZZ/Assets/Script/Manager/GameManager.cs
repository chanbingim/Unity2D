using System;
using UnityEngine;
using UnityEngine.Assertions.Must;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    public event    Action<Boolean> EnableChating;

    private         Boolean         m_EnableChating = false;
    private         string          m_szNextLevel;

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Return) || Input.GetKeyDown(KeyCode.KeypadEnter))
        {
            m_EnableChating = !m_EnableChating;
            EnableChating.Invoke(m_EnableChating);
        }

        if (Input.GetKeyDown(KeyCode.F5))
            GameClient.Get_Instance().Log_In("A", "1234");
    }

    #region public
    public void Change_Level(string szLevel)
    {
        m_szNextLevel = szLevel;
        Debug.Log("Next Level :" + m_szNextLevel);
        SceneManager.LoadScene("Loading");
    }

    public string   Get_NextLevel() { return m_szNextLevel; }
    public void     Add_ListenList(Action<Boolean> Event) { EnableChating += Event; }
    #endregion

    #region Private
    private void Initialize()
    {

    }
    #endregion

    #region SingleTon
    static GameManager m_pInstance = null;
    public static GameManager Get_Instance() { return m_pInstance; }

    void Awake()
    {
        if (null == m_pInstance)
        {
            m_pInstance = this;
            m_pInstance.Initialize();
            Debug.Log("Create Game Manager");
        }
        else
            Destroy(m_pInstance);
    }

    #endregion
}
