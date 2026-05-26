using UnityEngine;

public class InfomationUI : MonoBehaviour
{
    [SerializeField] ProgressComponent m_Hp = null;
    [SerializeField] ProgressComponent m_Stemina = null;

    [SerializeField] SkillUI m_SkillUI = null;

    private float m_fHp = 1000;

    private void Awake()
    {
        m_Hp.Initalize(m_fHp);
    }

    private void Update()
    {
        if(Input.GetKeyDown(KeyCode.PageUp))
        {
            m_fHp += 100f;
            m_Hp.SetValue(m_fHp);
        }

        if (Input.GetKeyDown(KeyCode.PageDown))
        {
            m_fHp -= 100f;
            m_Hp.SetValue(m_fHp);
        }

        if (Input.GetKeyDown(KeyCode.End))
        {
            m_SkillUI.Use_Skill();
        }
    }

}
