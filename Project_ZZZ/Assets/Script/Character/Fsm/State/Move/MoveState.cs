using GameFSM;
using InputCommand;
using System;
using Unity.VisualScripting;
using UnityEngine;

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
            moveCommand.m_Transform.position += moveCommand.m_vDir * Time.deltaTime * moveCommand.m_fSpeed;
        }
    }

    public void Exit()
    {

    }
}
