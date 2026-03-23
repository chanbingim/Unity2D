using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.Events;
using GameFSM;

public class Fsm
{
    [SerializeField]
    private float m_fMoveSpeed;
    private Vector3 m_fDirection;

    private IFSMState m_CurState;

    // 상태 만들고 상태안에서 이동움직임 처리하자
    public Vector3 Get_Direction() { return m_fDirection; }

    public void Change_State(IFSMState NewState)
    {
        if(m_CurState != NewState)
        {
            // 이전 상태 Exit 함수 호출
            m_CurState.Exit();

            // 새로운 상태로 변경후 Enter 이벤트 호출
            m_CurState = NewState;
            m_CurState.OnEnter();
        }
    }

    public void FSM_Update()
    {
        if(null != m_CurState)
            m_CurState.OnUpdate();
    }
}
