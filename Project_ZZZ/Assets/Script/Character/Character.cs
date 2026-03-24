using UnityEngine;
using InputCommand;

public class Character : MonoBehaviour
{
    public float       m_fRotationSpeed { get; set; }
    public float       m_fSpeed { get; set; }
    public float       m_Health { get; set; }

    [SerializeField]  protected Fsm     m_Character_Fsm = null;
    [SerializeField]  protected string  m_CurStateName = "";

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
       
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void HandleCommand(string StateName, ICommand command)
    {
        if (null != m_Character_Fsm)
        {
            if(m_CurStateName != StateName)
            {
                m_CurStateName = StateName;
                m_Character_Fsm.Change_State(StateName);
            }

            m_Character_Fsm.FSM_Update(command);
        }
    }
}
