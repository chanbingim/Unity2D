using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;
using UnityEngine.UI;
using UnityEngine.UIElements;

public class CUIAnimComponent : MonoBehaviour
{
    [System.Serializable]
    struct AnimationData
    {
        public float fAnimEventTime;
        public AnimProperty AnimPorperty;
    }

    [System.Serializable]
    struct AnimProperty
    {
        public Color vColor;
        public Vector3 vScale;
        public Vector4 vRotation;
        public Vector3 vPosition;
    }

    public UnityEvent FinishedEvent;
    private bool bIsEvnet = false;

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
    
    private RectTransform   m_rectTransform;
    private int m_iNumEvents = 0;
    private int m_iAnimIndex = 0;

    private float m_fAnimCurTime = 0;
    private Graphic m_Graphic = null;

    public void Play_Animtaion() { bIsAnimPlay = true; }
    public void Stop_Animtaion() { bIsAnimPlay = false; }

    // Start is called before the first frame update
    void Awake()
    {
        m_iNumEvents = AnimationEvents.Count;
        m_Graphic = GetComponent<Graphic>();
        m_rectTransform = GetComponent<RectTransform>();
    }

    // Update is called once per frame
    void Update()
    {
        if (false == bIsAnimPlay || m_iNumEvents < 2)
            return;

        m_fAnimCurTime += Time.deltaTime;
        var AnimationData = AnimationEvents[m_iAnimIndex + 1];
        var AnimProperty = AnimationData.AnimPorperty;

        var Cur_AnimationData = AnimationEvents[m_iAnimIndex];
        var Cur_AnimProperty = Cur_AnimationData.AnimPorperty;

        float fRatio = Mathf.Clamp(m_fAnimCurTime / AnimationData.fAnimEventTime, 0.0f, 1.0f);

        m_Graphic.color = Color.Lerp(Cur_AnimProperty.vColor, AnimProperty.vColor, fRatio);
        m_rectTransform.localRotation = Quaternion.Euler(Vector4.Lerp(Cur_AnimProperty.vRotation, AnimProperty.vRotation, fRatio));
        m_rectTransform.localScale = Vector3.Lerp(Cur_AnimProperty.vScale, AnimProperty.vScale, fRatio);
        m_rectTransform.anchoredPosition = Vector3.Lerp(Cur_AnimProperty.vPosition, AnimProperty.vPosition, fRatio);

        if (AnimationData.fAnimEventTime <= m_fAnimCurTime)
        {
            if (m_iAnimIndex < m_iNumEvents - 2)
            {
                m_iAnimIndex++;
                m_fAnimCurTime = 0;
            }
        }

        if (m_fAnimationTime <= m_fAnimCurTime)
        {
            if (0 < FinishedEvent.GetPersistentEventCount())
            {
                if (!bIsEvnet)
                {
                    FinishedEvent.Invoke();
                    bIsEvnet = true;
                }
            }

            if (false == m_bIsAnimationLoop)
                bIsAnimPlay = false;

            bIsEvnet = false;
            m_iAnimIndex = 0;
            m_fAnimCurTime = 0;
        }
    }

    public void    Initialize_Animtaion()
    {
        var Cur_AnimationData = AnimationEvents[0];
        var Cur_AnimProperty = Cur_AnimationData.AnimPorperty;

        m_Graphic.color = Cur_AnimProperty.vColor;
        m_rectTransform.localRotation = Quaternion.Euler(Cur_AnimProperty.vRotation);
        m_rectTransform.localScale = Cur_AnimProperty.vScale;
        m_rectTransform.anchoredPosition = Cur_AnimProperty.vPosition;

        m_fAnimCurTime = 0f;
    }
}
