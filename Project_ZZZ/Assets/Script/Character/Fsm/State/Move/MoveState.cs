using GameFSM;
using InputCommand;
using UnityEngine;

public class MoveState : IFSMState
{
    private float m_Velocity = 100; // SmoothDamp용

    public MoveState()
    {

    }

    public void OnEnter()
    {

    }

    public void OnUpdate(ICommand Command)
    {
        if (null != Command)
        {
            CMoveCommand moveCommand = (CMoveCommand)Command;
            Transform transform = moveCommand.m_Transform;
            Vector3 vDir = moveCommand.m_vDir - transform.position;

            // Translate 오브젝트의 로컬 좌표에서 움직이는거임
            // 월드를 곱해서 월드공간으로 오게되면 결국 회전을 먹어서 특정 위치로 감
            // 위치 - SmoothDamp (관성느낌)

            transform.position = moveCommand.m_vDir;
        }
    }

    public void Exit()
    {

    }
}
