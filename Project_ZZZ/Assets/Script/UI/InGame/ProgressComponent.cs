using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class ProgressComponent : MonoBehaviour
{
    public float FrontImageRatio => m_CurRatio;

    [SerializeField] float  LerpTime;
    [SerializeField] Text   ValueText = null;

    [SerializeField] Image FrontImage = null;
    [SerializeField] Image BackImage = null;

    private Coroutine   m_Corutine = null;
    private float       m_CurValue;
    private float       m_MaxValue;
    private float       m_CurRatio;

    public void Initalize(float fMaxValue)
    {
        m_CurValue = m_MaxValue = fMaxValue;
        m_CurRatio = 1f;
        SetTextValue();
    }

    public void SetValue(float fValue)
    {
        m_CurValue = Mathf.Clamp(fValue, 0, m_MaxValue);
        m_CurRatio = Mathf.Clamp01(fValue / m_MaxValue);
        if(FrontImage != null)
            FrontImage.fillAmount = m_CurRatio;

        SetTextValue();
        if (m_Corutine != null)
            StopCoroutine(m_Corutine);

        m_Corutine = StartCoroutine(LerpAnimation());
    }

    private void SetTextValue()
    {
        if (ValueText)
        {
            ValueText.text = m_CurValue.ToString() + "/" + m_MaxValue.ToString();
        }
    }

    IEnumerator LerpAnimation()
    {
        if (BackImage == null)
            yield break;

        float StartPreRatio = BackImage.fillAmount;
        float AccTime = 0;

        while (AccTime < LerpTime)
        {
            AccTime += Time.deltaTime;
            BackImage.fillAmount = Mathf.MoveTowards(StartPreRatio, m_CurRatio, AccTime / LerpTime);

            yield return null;
        }

        m_Corutine = null;
    }
}
