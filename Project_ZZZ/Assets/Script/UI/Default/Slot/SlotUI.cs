using UnityEngine;
using UnityEngine.EventSystems;
using UnityEngine.UI;

public abstract class SlotUI<T> : MonoBehaviour, IPointerClickHandler
{
    public const float DOUBLE_CLICK_TIME = 0.25f;
    [SerializeField] protected Image SlotImage;

    protected int SlotIndex;
    private float LastClickTime;

    public void OnPointerClick(PointerEventData eventData)
    {
        if (Time.time - LastClickTime <= DOUBLE_CLICK_TIME)
        {
            OnDoubleClicked(eventData);
        }
        else
        {
            OnClick(eventData);
        }

        LastClickTime = Time.time;
    }

    public void SetSlotImage(Sprite sprite)
    {
        // 여기서 Image도 채우기
        SlotImage.sprite = sprite;
    }

    public virtual bool Empty()
    {
        return true;
    }

    public virtual void Clear()
    {
        SlotImage.sprite = null;
    }

    protected virtual void OnClick(PointerEventData eventData) { }
    protected virtual void OnDoubleClicked(PointerEventData eventData) { }
    protected virtual void OnBeginDrag() { }
    protected virtual void OnDrag() { }
    protected virtual void OnEndDrag() { }
    protected virtual void OnDrop(SlotUI<T> target) { }
    protected virtual void Swap(SlotUI<T> other)
    {
        Sprite Tempsprite = other.SlotImage.sprite;
        other.SlotImage.sprite = SlotImage.sprite;
        SlotImage.sprite = Tempsprite;
    }
}
