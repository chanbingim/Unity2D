using UnityEngine;
using UnityEngine.Events;

public class CTittle_BackGround : MonoBehaviour
{
    public UnityEvent                           m_PressedEvent;

    [SerializeField] private GameObject         m_PressedText;
    private bool                                m_bWaitingForClick = true;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (!m_bWaitingForClick) return;

        if (Input.anyKeyDown)
        {
            if (0 < m_PressedEvent.GetPersistentEventCount())
            {
                m_PressedEvent.Invoke();
                m_PressedText.SetActive(false);
                m_bWaitingForClick = false;
            }
        }
    }

    public void Active_TitleLogic()
    {
        m_bWaitingForClick = true;
        m_PressedText.SetActive(true);
    }
}
