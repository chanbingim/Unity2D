using System;
using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine.UI;
using UnityEngine.Events;
using UnityEngine;
using System.Data;

public class CUIAnimComponent : MonoBehaviour
{
    [System.Serializable]
    struct AnimationData
    {
       public  float        fAnimEventTime;
       public AnimProperty  AnimPorperty;
    }

    [System.Serializable]
    struct AnimProperty
    {
        public  Color       vColor;
        public  Vector3     vScale;
        public  Vector4     vRotation;
        public  Vector3     vPosition;
    }

    public UnityEvent FinishedEvent;
    private bool    bIsEvnet = false;

    [SerializeField]
    private bool bIsAnimPlay = false;
    // UI Animation의 경우
    // 재생 시간 안에서
    // 알파 변경, 크기 변경, 회전 변경, 위치 변경의 애니메이션 필요하다.
    // 파티클도 있으면 필요한데 이거는 공부해서 집어넣자.
    [SerializeField]
    private float m_fAnimationTime = 0;

    [SerializeField]
    private bool m_bIsAnimationLoop = false;

    [SerializeField]
    private List<AnimationData> AnimationEvents;

    private Color       m_StartColor;
    private Vector3     m_vStartPosition;
    private Quaternion  m_vStartRotation;
    private Vector3     m_vStartScale;

    private int         m_iNumEvents = 0;
    private int         m_iAnimIndex = 0;

    private float       m_fAnimCurTime = 0;
    private Graphic     m_Graphic = null;

    public void Play_Animtaion() { bIsAnimPlay = true; }
    public void Stop_Animtaion() { bIsAnimPlay = false; }

    // Start is called before the first frame update
    void Start()
    {
        m_iNumEvents = AnimationEvents.Count;
        m_Graphic = GetComponent<Graphic>();
        InitAnimState();
    }

    // Update is called once per frame
    void Update()
    {
        if (false == bIsAnimPlay)
            return;

        m_fAnimCurTime += Time.deltaTime;
        var AnimationData = AnimationEvents[m_iAnimIndex];
        var AnimProperty = AnimationData.AnimPorperty;

        float fRatio = Mathf.Clamp(m_fAnimCurTime / AnimationData.fAnimEventTime, 0.0f, 1.0f);

        m_Graphic.color = Color.Lerp(m_StartColor, AnimProperty.vColor, fRatio);
        transform.localRotation = Quaternion.Lerp(m_vStartRotation, Quaternion.Euler(AnimProperty.vRotation), fRatio);
        transform.localScale = Vector3.Lerp(m_vStartScale, AnimProperty.vScale, fRatio);
        transform.localPosition = Vector3.Lerp(m_vStartPosition, AnimProperty.vPosition, fRatio);

        if (AnimationData.fAnimEventTime <= m_fAnimCurTime)
        {
            if(m_iAnimIndex < m_iNumEvents - 1)
            {
                m_iAnimIndex++;
                m_fAnimCurTime = 0;
                InitAnimState();
            }
        }

        if(m_fAnimationTime <= m_fAnimCurTime)
        {
            if(0 < FinishedEvent.GetPersistentEventCount())
            {
                if (!bIsEvnet)
                {
                    FinishedEvent.Invoke();
                    bIsEvnet = true;
                }
            }

            if (m_bIsAnimationLoop)
            {
                m_iAnimIndex = 0;
                m_fAnimCurTime = 0;
                InitAnimState();
                bIsEvnet = false;
            }
        }
    }

    private void InitAnimState()
    {
        m_StartColor = m_Graphic.color;
        m_vStartRotation = transform.localRotation;
        m_vStartPosition = transform.localPosition;
        m_vStartScale = transform.localScale;
    }
}
