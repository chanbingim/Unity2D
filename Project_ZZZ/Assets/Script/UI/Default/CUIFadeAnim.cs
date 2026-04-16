using System;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.UI;

public class CUIFadeAnim : MonoBehaviour
{
    public enum FADE_TYPE { LEVEL_CHANGE, MOVE_POSITION, END };
    public Material mat;
    public float Duration = 2.0f;

    [SerializeField] private FADE_TYPE  m_FadeType;
    [SerializeField] private String     m_szNextLevel;

    private bool        m_bIsAnimPlay = false;
    private Graphic     m_Graphic = null;
    private Color       m_Color = Color.black;
    private float       m_curTime;

    void Start()
    {
        m_Graphic = GetComponent<Graphic>();
    }

    public void Play_Animtaion()
    {
        gameObject.SetActive(true);
        m_Color.a = 0.0f;
        m_bIsAnimPlay = true;
    }

    public void Stop_Animtaion() { m_bIsAnimPlay = false; }
    void Update()
    {
        if (!m_bIsAnimPlay)
            return;

        m_curTime += Time.deltaTime;

        m_Color.a = Mathf.Lerp(0, 1, m_curTime / 0.3f);
        m_Graphic.color = m_Color;
        mat.SetFloat("_Progress", m_curTime / 1f);
        mat.SetFloat("_MirrorTiling", 2);

        if (m_curTime > Duration)
        {
            m_curTime = 0;
            Anim_FinishedEvent();
        }
    }

    private void Anim_FinishedEvent()
    {
        switch (m_FadeType)
        {
            case FADE_TYPE.LEVEL_CHANGE:
                GameManager.Get_Instance().Change_Level(m_szNextLevel);
                break;
        }
    }
}
