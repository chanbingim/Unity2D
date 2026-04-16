using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.UI;

public class Login_UI : MonoBehaviour
{
    public UnityEvent                           m_OutBoundClick;
    public UnityEvent                           m_LoginSuccessEvent;

    [SerializeField] private CUIAnimComponent   m_AnimComponent;
    [SerializeField] private InputField         m_InputFieldID;
    [SerializeField] private InputField         m_InputFieldPW;

    private RectTransform                       m_RectTransform;
    private bool                                m_bIsActive = false;
    private GameClient                          m_gameClient = null;

    void Awake()
    {
        m_AnimComponent = GetComponent<CUIAnimComponent>();
        m_RectTransform = GetComponent<RectTransform>();
        m_gameClient = GameClient.Get_Instance();
    }

    // Update is called once per frame
    void Update()
    {
        if (!m_bIsActive) return;

        if (Input.GetMouseButtonDown(0))
        {
            if (!RectTransformUtility.RectangleContainsScreenPoint(
                m_RectTransform,
                Input.mousePosition,
                null))
            {
                gameObject.SetActive(false);
                m_bIsActive = false;
                m_OutBoundClick.Invoke();
            }
        }
    }

    private void OnDestroy()
    {
        //m_gameClient.m_LoginEvent -= Login_Event;
    }

    public void Active_LoginUI()
    {
        gameObject.SetActive(true);
        m_AnimComponent.Initialize_Animtaion();
        m_AnimComponent.Play_Animtaion();
    }

    public void Active_LoginLogic()
    {
        m_bIsActive = true;
    }

    public void Login_Button()
    {
        //m_gameClient.Log_In(m_InputFieldID.text, m_InputFieldPW.text);
        //m_gameClient.m_LoginEvent += Login_Event;
        Login_Event(true);
    }

    public void Login_Event(bool bIsSuccess)
    {
        if(bIsSuccess)
        {
            m_LoginSuccessEvent.Invoke();
        }
        else
        {

        }
    }
}
