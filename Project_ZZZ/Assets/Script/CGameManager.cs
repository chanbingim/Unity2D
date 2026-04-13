using UnityEngine;
using UnityEngine.SceneManagement;


// 클래스의 명.변수명 또는 함수명 이런방식으로 써야함
// 하지만 클래스명. 을 제거하는방법은 아래 처럼 하면됨
using static Defines;

public class CUtilyManager
{
    private static CUtilyManager    pInstance = null;
 

    private Vector2Int vScreenSize;
    private string szNextLevel;

    #region public
    public Vector2Int Get_GameScreenSize() { return vScreenSize; }

    public void Change_Level(string szLevel)
    {
        szNextLevel = szLevel;
        Debug.Log("Next Level :" + szNextLevel);
        SceneManager.LoadScene("Loading");
    }

    public string Get_NextLevel() { return szNextLevel; }

    #endregion

    #region private
    private RESULT Initialize()
    {
        Debug.Log("Create GameManager");
        vScreenSize = new Vector2Int(Screen.width, Screen.height);

        return RESULT.SUCCESS;
    }
    #endregion

    #region Default
    private CUtilyManager()
    {

    }

    public static CUtilyManager Get_Instance()
    {
        if (null == pInstance)
        {
            pInstance = new CUtilyManager();
            if (RESULT.FAIL == pInstance.Initialize())
                return null;
        }
        return pInstance;
    }
    #endregion
}
