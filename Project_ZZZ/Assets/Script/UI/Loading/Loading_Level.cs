using System.Collections;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.SceneManagement;
using UnityEngine.UI;

public class Loading_Level : MonoBehaviour
{
    public UnityEvent LoadSceneEvent;
    public UnityEvent LoadCompletedEvent;

    [SerializeField]
    private Slider LoadingBar = null;

    [SerializeField]
    private float Max_LoadTime = 0;
    private float m_fCurTime = 0;

    private void Start()
    {
        LoadScene();
    }

    public void LoadScene()
    {
        if (0 < LoadSceneEvent.GetPersistentEventCount())
            LoadSceneEvent.Invoke();

        StartCoroutine(LoadingAsync(GameManager.Get_Instance().Get_NextLevel()));
    }

    // 코루틴 
    IEnumerator LoadingAsync(string name)
    {
        AsyncOperation asyncOperation = SceneManager.LoadSceneAsync(name);
        asyncOperation.allowSceneActivation = false; //로딩이 완료되는대로 씬을 활성화할것인지

        while (!asyncOperation.isDone)
        {
            m_fCurTime += Time.deltaTime;
            float fRatio = m_fCurTime / Max_LoadTime;
            if (null != LoadingBar)
                LoadingBar.value = fRatio;

            //이건 로딩이 너무 빨라서 작성한거라, 무거운 씬 로딩할땐 시간 체크하는 부분은
            //생략해도 무방하다!
            bool bIsComplete = false;
            if (asyncOperation.progress >= 0.9f && fRatio >= 1.0f)
            {
                bIsComplete = true;
                if (0 < LoadCompletedEvent.GetPersistentEventCount())
                    LoadCompletedEvent.Invoke();
            }

            if (bIsComplete && Input.anyKeyDown)
            {
                asyncOperation.allowSceneActivation = true;
            }

            yield return null;
        }
    }
}
