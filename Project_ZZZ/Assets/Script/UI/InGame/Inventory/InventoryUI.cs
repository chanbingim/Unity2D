using UnityEngine;
using UnityEngine.UI;
using Nettention.Proud;

public class InventoryUI : MonoBehaviour
{
    public enum InvenTag : int { EQUIPMENT = 1, CONSUME, GITA, END};

    //List<InvenSlot>[]       invenSlots = new List<InvenSlot>[(int)InvenTag.END];

    [SerializeField] Text      TttleText = null;
    [SerializeField] Text      GoldText = null;

    InvenTag        m_SelectTag = InvenTag.EQUIPMENT;
    bool            m_bIsActive = false;

    private void Start()
    {
        var Instance = UIManager.Get_Instance();
        Instance.Register(KeyCode.I, ToggleInventoryVisible);

        GameClient.Get_Instance().Bind_ResponeGoldEvent(Respone_GoldAmount);
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

    bool Respone_GoldAmount(HostID hostID, RmiContext rmiContext, int ClientID, int Amount)
    {
        if(GoldText == null) return false;

        GoldText.text = Amount.ToString();
        return true;
    }
}
