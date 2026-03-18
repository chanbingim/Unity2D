using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.UI;

public class CUIFadeAnim : MonoBehaviour
{
    public Material mat;

    [SerializeField]
    private bool bIsAnimPlay = false;

    [SerializeField]
    public float Duration = 2.0f;

    private Graphic m_Graphic = null;
    private Color m_Color = Color.black;
    private float m_curTime;

    void Start()
    {
        m_Graphic = GetComponent<Graphic>();
    }

    public void Play_Animtaion() {
        gameObject.SetActive(true);
        m_Color.a = 0.0f;
        bIsAnimPlay = true; 
    }
    public void Stop_Animtaion() { bIsAnimPlay = false; }

    public UnityEvent FinishedEvent;

    void Update()
    {
        if(!bIsAnimPlay)
            return;

        m_curTime += Time.deltaTime;

        m_Color.a = Mathf.Lerp(0, 1, m_curTime / 0.3f);
        m_Graphic.color = m_Color;
        mat.SetFloat("_Progress", m_curTime / 1f);
        mat.SetFloat("_MirrorTiling", 2);

        if (m_curTime > Duration)
        {
            m_curTime = 0;
            FinishedEvent.Invoke();
        }
    }
}
