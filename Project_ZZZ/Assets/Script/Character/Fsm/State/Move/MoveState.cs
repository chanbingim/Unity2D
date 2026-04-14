using GameFSM;
using InputCommand;
using UnityEngine;
using UnityEngine.Assertions.Must;

public class MoveState : IFSMState
{
    public MoveState()
    {

    }

    public void OnEnter()
    {

    }

    public void OnUpdate(Character character, ICommand Command)
    {
        CMoveCommand moveCommand = Command as CMoveCommand;
        character.Move(moveCommand.m_vDir);
    }

    public void Exit()
    {

    }
}
