using UnityEngine;
using static Defines;

public class CPopupBase : MonoBehaviour
{
    protected RectTransform     m_RectTransform = null;
    protected bool              m_bIsActive = false;
    protected GameClient        m_gameClient = null;

    protected virtual RESULT    Initialize() { return RESULT.SUCCESS; }
}
