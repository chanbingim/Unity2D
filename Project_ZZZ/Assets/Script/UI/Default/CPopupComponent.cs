using System.Collections;
using UnityEngine.UI;
using UnityEngine;

public class ErrorPopupComponent : CPopupBase
{
    [SerializeField] private Text   m_Text = null;

    void Awake()
    {

    }

    public void Open_Popup(string szMsg)
    {
        m_Text.text = szMsg;
    }

    public void Close()
    {
        UIManager UIMgr = UIManager.Get_Instance();
        UIMgr.Close_ActivePopup(gameObject.GetComponent<CPopupBase>());
    }
}
