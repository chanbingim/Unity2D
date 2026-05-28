using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class InventoryUI : MonoBehaviour
{
    public enum InvenTag : int { EQUIPMENT = 1, CONSUME, GITA, END};

    //List<InvenSlot>[]       invenSlots = new List<InvenSlot>[(int)InvenTag.END];

    [SerializeField] Text      TttleText = null;

    InvenTag        m_SelectTag = InvenTag.EQUIPMENT;
    bool            m_bIsActive = false;

    private void Start()
    {
        var Instance = UIManager.Get_Instance();
        Instance.Register(KeyCode.I, ToggleInventoryVisible);

        gameObject.SetActive(false);
    }

    public void SelectTag(int tag)
    {
        m_SelectTag = (InvenTag)tag;
        Change_TattleText();
    }

    void ToggleInventoryVisible()
    {
        m_bIsActive = !m_bIsActive;
        gameObject.SetActive(m_bIsActive);
    }

    void Change_TattleText()
    {
        if (TttleText == null)
            return;

        TttleText.text = m_SelectTag.ToString();
    }
}
