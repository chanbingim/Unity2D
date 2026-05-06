using UnityEngine;

public class RewordComponent : InteractableComponent
{
    [SerializeField] private ScriptableObject m_Dropcomponent;

    override public void OnInteract(InteractorComponent actor)
    {
        DropComponent DropComponent = m_Dropcomponent as DropComponent;

        int iItemIndex = DropComponent.Get_DropItemIndex();
        if (-1 == iItemIndex)
        {
            Debug.LogErrorFormat("[RewordComponent] Item Index : -1");
            return;
        }

        GameObject ItemPrefab = CResourceManager.Get_Instance().Get_Prefab("Item");
        GameObject.Instantiate(ItemPrefab);
    }
}
