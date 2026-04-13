using System;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.SceneManagement;


// 클래스의 명.변수명 또는 함수명 이런방식으로 써야함
// 하지만 클래스명. 을 제거하는방법은 아래 처럼 하면됨
using static Defines;

public class CInputManager
{
    public event Action<Boolean>    EnableChating;
    private Boolean                 m_EnableChating = false;

    public void Update()
    {
        if (Input.GetKeyDown(KeyCode.Return) || Input.GetKeyDown(KeyCode.KeypadEnter))
        {
            m_EnableChating = !m_EnableChating;
            EnableChating.Invoke(m_EnableChating);
        }
    }

    #region private
    private RESULT Initialize()
    {
        Debug.Log("Create Input manager");

        return RESULT.SUCCESS;
    }
    #endregion

    #region Default
    private CInputManager()
    {

    }

    public static CInputManager Create()
    {
        CInputManager pInstance = new CInputManager();
        if (RESULT.FAIL == pInstance.Initialize())
            return null;

        return pInstance;
    }

    #endregion
}
