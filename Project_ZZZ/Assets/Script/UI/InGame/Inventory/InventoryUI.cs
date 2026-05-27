using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InventoryUI : MonoBehaviour
{
    public enum InvenTag : int { EQUIP = 1, CONSUME, GITA, END};

    List<InvenSlot>[]       invenSlots = new List<InvenSlot>[(int)InvenTag.END];

    public void SetInventoryVisible(bool bFlag)
    {
        gameObject.SetActive(bFlag);
    }
}
