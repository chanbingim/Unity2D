using UnityEngine;
using UnityEngine.UI;

public class PopUpUI : MonoBehaviour
{
    [SerializeField] private Text   m_Text = null;

    void Start()
    {
        
    }

    public void Open_Popup(string text)
    {
        m_Text.text = text;
    }

    public void Close()
    {
        gameObject.SetActive(false);
    }
}
