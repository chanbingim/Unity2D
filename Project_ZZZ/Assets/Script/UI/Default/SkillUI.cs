using System.Collections;
using UnityEngine;
using UnityEngine.UI;

public class SkillUI : MonoBehaviour
{
    [SerializeField] Texture2D  m_BaseTex = null;
    [SerializeField] Image      m_Image = null;
    [SerializeField] Text       m_Text = null;

    Material                    m_Mat = null;
    Texture2D                   m_SkillTex = null;
    int                         m_SkillID = 0;

    float                       m_CurCoolTime = 0;
    float                       m_MaxCoolTime = 1;
    bool                        m_bIsCoolTime = false;
    Coroutine                   m_Coroutine = null;

    public   bool               IsCoolTime() { return m_bIsCoolTime; }

    void Start()
    {
        if(m_Text != null )
            m_Text.gameObject.SetActive( false );

        if (m_Image != null )
        {
            m_Mat = Instantiate(m_Image.material);
            m_Image.material = m_Mat;

            m_Mat.SetTexture("_BaseTexture", m_BaseTex);
        }
    }

    public void SetSkillID(int skillID) 
    { 
        // 데이터를 찾아서 Tex 까지 세팅
        m_SkillID = skillID;

        m_SkillTex = null;
        //m_Mat.SetTexture("FrontTexture", m_SkillTex);
    }

    public void Use_Skill()
    {
        if (m_bIsCoolTime)
            return;

        if (m_Coroutine != null)
        {
            StopCoroutine(m_Coroutine);
            m_Coroutine = null;
        }

        m_CurCoolTime = 0f;
        m_Text.gameObject.SetActive(true);
        m_bIsCoolTime = true;
        m_Mat.SetFloat("_bIsCoolTime", 1f);

        m_Coroutine = StartCoroutine(CoolTime());
    }

    void   SetCoolTimeText()
    {
        m_Text.text = (m_MaxCoolTime - m_CurCoolTime).ToString("F1");
    }

    IEnumerator CoolTime()
    {
        while (m_CurCoolTime < m_MaxCoolTime)
        {
            m_CurCoolTime += Time.deltaTime;
            m_Mat.SetFloat("_Angle", 1f - (m_CurCoolTime / m_MaxCoolTime));
            SetCoolTimeText();

            yield return null;
        }

        m_Mat.SetFloat("_bIsCoolTime", 0f);
        m_Text.gameObject.SetActive(false);
        m_Coroutine = null;
        m_bIsCoolTime = false;
    }
}
