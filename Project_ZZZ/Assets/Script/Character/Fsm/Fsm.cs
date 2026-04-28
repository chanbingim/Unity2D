using GameFSM;
using InputCommand;
using System.Collections.Generic;
using UnityEngine;

public class Fsm
{
    [SerializeField] protected float m_fMoveSpeed;
    protected Vector3 m_fDirection;

    protected Dictionary<string, IFSMState> Dic_State = new Dictionary<string, IFSMState>();
    protected IFSMState     m_CurState;

    // 상태 만들고 상태안에서 이동움직임 처리하자
    public Vector3 Get_Direction() { return m_fDirection; }
    protected GameClient            m_GameClient = null;

    public virtual void Change_State(string StateName)
    {
        IFSMState NewState = null;
        if (Dic_State.ContainsKey(StateName))
            NewState = Dic_State[StateName];

        if (null == NewState)
        {
#if DEBUG
            Debug.Log("Not Find FSM State");
#endif
            return;
        }

        if (m_CurState != NewState)
        {
            if (null != m_CurState)
                m_CurState.Exit();    // 이전 상태 Exit 함수 호출

            // 새로운 상태로 변경후 Enter 이벤트 호출
            m_CurState = NewState;
            m_CurState.OnEnter();
        }
    }

    public virtual void FSM_Update(Character character, CBaseCommand command)
    {
        if (null != m_CurState)
            m_CurState.OnUpdate(character, command);
    }
}
