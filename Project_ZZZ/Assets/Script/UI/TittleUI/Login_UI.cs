using UnityEngine;
using UnityEngine.Events;
using UnityEngine.UI;
using static UIManager;
using static Defines;

public class Login_UI : CPopupBase
{
    public UnityEvent                           m_OutBoundClick;
    public UnityEvent                           m_LoginSuccessEvent;

    [SerializeField] private CUIAnimComponent   m_AnimComponent;
    [SerializeField] private InputField         m_InputFieldID;
    [SerializeField] private InputField         m_InputFieldPW;
    private string                              m_ErrorMsg = "";

    void Awake()
    {
        m_AnimComponent = GetComponent<CUIAnimComponent>();
        m_RectTransform = GetComponent<RectTransform>();
        m_gameClient = GameClient.Get_Instance();
        m_gameClient.ServerLoginHandler.ResultEvent += Login_Event;
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
        m_gameClient.ServerLoginHandler.ResultEvent -= Login_Event;
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
        m_gameClient.Log_In((int)LOGIN_TYPE.LOCAL, m_InputFieldID.text, m_InputFieldPW.text, "");
    }

    public void Login_Event(bool bIsSuccess, int LoginMsg)
    {
        if(bIsSuccess)
        {
            m_LoginSuccessEvent.Invoke();
        }
        else
        {
            if(1 == LoginMsg)
                m_ErrorMsg = "아이디가 틀렸습니다.";
            else if (2 == LoginMsg)
                m_ErrorMsg = "비밀번호가 틀렸습니다";

            UIManager pUImgr = UIManager.Get_Instance();
            pUImgr.Show_UI(POPUP_TYPE.ERREOR, Show_Erreor);
        }
    }

    public void Show_Erreor(CPopupBase Popup)
    {
        ErrorPopupComponent ErrorCom = Popup.gameObject.GetComponent<ErrorPopupComponent>();
        ErrorCom.Open_Popup(m_ErrorMsg);
    }
}
