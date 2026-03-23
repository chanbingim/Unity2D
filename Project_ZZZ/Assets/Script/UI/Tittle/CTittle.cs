using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class CTittle : MonoBehaviour
{
    // 여기서 데이터 로딩도하고 텍스처도 바꾸고 이런 동작 한다고 치자
    // Start is called before the first frame update
    public UnityEvent OnClicked;
    private bool bIsClicked = false;

    void Awake()
    {

    }

    // Update is called once per frame
    void Update()
    {
        if (true == bIsClicked)
            return;

        if (Input.anyKeyDown)
        {
            if (0 < OnClicked.GetPersistentEventCount())
            {
                OnClicked.Invoke();
                bIsClicked = true;
            }
        }
    }

    public void Change_Scene()
    {
        CUtilyManager.Get_Instance().Change_Level("Lobby");
    }

}
