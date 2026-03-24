using GameFSM;
using InputCommand;
using System;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.UIElements;

public class MoveState : IFSMState
{
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

            transform.LookAt(transform.position + moveCommand.m_vDir);
            // Translate 오브젝트의 로컬 좌표에서 움직이는거임
            // 월드를 곱해서 월드공간으로 오게되면 결국 회전을 먹어서 특정 위치로 감
            transform.Translate(Vector3.forward * Time.deltaTime * moveCommand.m_fSpeed);
        }
    }

    public void Exit()
    {

    }
}
