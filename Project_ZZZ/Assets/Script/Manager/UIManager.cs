using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.Pool;
using static Defines;

public class UIManager : MonoBehaviour
{
    public enum POPUP_TYPE { INVEN, ERREOR, END};

    [System.Serializable]
    public class PopupPrefabEntry
    {
        public POPUP_TYPE type;
        public CPopupBase prefab;
    }

    public delegate void KeyInputHandler();
    private Dictionary<KeyCode, KeyInputHandler> _bindings
     = new Dictionary<KeyCode, KeyInputHandler>();

    [SerializeField]
    private List<PopupPrefabEntry>              m_PopupPrefabList = new List<PopupPrefabEntry>();
    private Dictionary<POPUP_TYPE, CPopupBase>  m_PopupPrefabs = new Dictionary<POPUP_TYPE, CPopupBase>();
    private Dictionary<POPUP_TYPE, CPopupBase>  m_UniquePopupUIs = new Dictionary<POPUP_TYPE, CPopupBase>();
    
    private Dictionary<POPUP_TYPE, CObjectPool<CPopupBase>>  m_PopupUIs = new Dictionary<POPUP_TYPE, CObjectPool<CPopupBase>>();
    private List<CPopupBase>                                 m_ActivePopups = new List<CPopupBase>();
    [SerializeField] private Canvas m_Canvas;

    public void Update()
    {
        foreach (var binding in _bindings)
        {
            if (Input.GetKeyDown(binding.Key))
            {
                binding.Value?.Invoke();
            }
        }
    }

    public void Register(KeyCode key, KeyInputHandler handler)
    {
        if (_bindings.ContainsKey(key))
        {
            Debug.Log("Already Bind Key");
            return;
        }

        _bindings.Add(key, handler);
    }

    public void Unregister(KeyCode key, KeyInputHandler handler)
    {
        if (_bindings.ContainsKey(key))
            _bindings[key] -= handler;
    }

    public RESULT  Initialize()
    {
        m_PopupPrefabs = m_PopupPrefabList.ToDictionary(x => x.type, x => x.prefab);
        for (POPUP_TYPE Type = POPUP_TYPE.INVEN; Type < POPUP_TYPE.END; ++Type)
        {
            if (POPUP_TYPE.ERREOR != Type)
                Create_UniquePopup(Type);
            else
                Create_Popup(Type);
        }

        return RESULT.SUCCESS;
    }

    public void Show_UI(POPUP_TYPE Type, Action<CPopupBase> action = null)
    {
        CPopupBase pPopup = null;
        if(POPUP_TYPE.ERREOR != Type)
            pPopup = Create_UniquePopup(Type);
        else
            pPopup = Create_Popup(Type);

        pPopup.gameObject.SetActive(true);
        m_ActivePopups.Add(pPopup);
        action?.Invoke(pPopup);
    }

    public void Close_ActivePopup(CPopupBase popupUI)
    {
        if (m_ActivePopups.Count <= 0)
        {
            Debug.Log("Empty Active popup");
            return;
        }

        int last = m_ActivePopups.Count - 1;
        var popup = m_ActivePopups[last];

        m_ActivePopups.RemoveAt(last);
        popup.gameObject.SetActive(false);
    }

    public void All_Close()
    {
        foreach (var Obj in m_ActivePopups)
            Obj.gameObject.SetActive(false);

        m_ActivePopups.Clear();
    }

    private CPopupBase Create_UniquePopup(POPUP_TYPE Type)
    {
        CPopupBase pPopup = null; 
        CPopupBase pPrefabPopup = null;

        if(!m_UniquePopupUIs.TryGetValue(Type, out pPopup))
        {
            if (!m_PopupPrefabs.TryGetValue(Type, out pPrefabPopup))
                return null;

            pPopup = GameObject.Instantiate(pPrefabPopup, m_Canvas.gameObject.transform);
            pPopup.gameObject.SetActive(false);
            m_UniquePopupUIs.Add(Type, pPopup);
        }

        return pPopup;
    }

    private CPopupBase Create_Popup(POPUP_TYPE Type)
    {
        CObjectPool<CPopupBase> pPopupList = null;
        CPopupBase pPrefabPopup = null;

        if (!m_PopupUIs.TryGetValue(Type, out pPopupList))
        {
            if (!m_PopupPrefabs.TryGetValue(Type, out pPrefabPopup))
                return null;

            pPopupList = CObjectPool<CPopupBase>.Create_Pool(() =>
            {
                CPopupBase obj = GameObject.Instantiate(pPrefabPopup, m_Canvas.transform);
                obj.gameObject.SetActive(false);
                return obj;
            }, 50);

            m_PopupUIs.Add(Type, pPopupList);
        }

        return pPopupList.GetObject();
    }
    
    #region SingleTon
    static UIManager m_pInstance = null;
    public static UIManager Get_Instance() { return m_pInstance; }
    void Awake()
    {
        if (null == m_pInstance)
        {
            m_pInstance = this;
            m_pInstance.Initialize();
            DontDestroyOnLoad(m_pInstance);
            Debug.Log("Create UI Manager");
        }
        else
            Destroy(m_pInstance);
    }
    #endregion
}
