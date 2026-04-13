using UnityEngine;
using static Defines;

public class UIManager
{
    static UIManager        m_pInstance = null;

    public static UIManager Create(Canvas MianCanvas)
    {
        m_pInstance = new UIManager();

        if(RESULT.FAIL == m_pInstance.Initialize())
            return null;

        return m_pInstance;
    }

    private RESULT  Initialize()
    {



        return RESULT.SUCCESS;
    }

}
