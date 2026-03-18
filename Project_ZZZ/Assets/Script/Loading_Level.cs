using System;
using System.Collections;
using System.Collections.Generic;
using System.Numerics;
using Unity.VisualScripting;
using UnityEngine;
using System.Collections.Generic;
using UnityEngine.SceneManagement;

public class Loading_Level : MonoBehaviour
{
    [SerializeField]
    public List<Texture2D> BackTex = null;

    [SerializeField]
    private bool bIsFinished = false;

    [SerializeField]
    private bool bIsFadeAnim = false;

    [SerializeField]
    private float CurTime = 0;

    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        CurTime += Time.deltaTime;

        if(CurTime > 2.0f)
        {
            SceneManager.LoadScene(CGameManager.Get_Instance().Get_NextLevel());
        }
        


    }
}
