using System;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using static Defines;

public class UIManager : MonoBehaviour
{
    public enum POPUP_TYPE { INVEN, ERREOR, END};

    private Dictionary<POPUP_TYPE, GameObject>  m_PopupPrefabs = new Dictionary<POPUP_TYPE, GameObject>();
    private Dictionary<POPUP_TYPE, GameObject>  m_PopupUIs = new Dictionary<POPUP_TYPE, GameObject>();
    private Stack<GameObject>                   m_ActivePopups = new Stack<GameObject>();

    public void Update()
    {
        
    }

    public RESULT  Initialize()
    {
        return RESULT.SUCCESS;
    }

    #region SingleTon
    static UIManager m_pInstance = null;
    public static UIManager Get_Instance() { return m_pInstance; }
    void Awake()
    {
        if (null == m_pInstance)
        {
            m_pInstance = this;
            GameClient.Get_Instance();
            Debug.Log("Create UI Manager");
        }
        else
            Destroy(m_pInstance);
    }
    #endregion
}
