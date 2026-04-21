using GameFSM;
using InputCommand;
using UnityEngine;
using UnityEngine.Assertions.Must;

public class MoveState : IFSMState<PlayerFSM.ANIM_STATE>
{
    public PlayerFSM.ANIM_STATE Type => PlayerFSM.ANIM_STATE.MOVE;
    public MoveState()
    {

    }

    public void OnEnter()
    {

    }

    public void OnUpdate(Character character, ICommand Command)
    {
        CMoveCommand moveCommand = Command as CMoveCommand;
        Vector3 Dir = moveCommand.m_vDir * moveCommand.m_fSpeed * Time.deltaTime;

        character.Move(Dir);
    }

    public void Exit()
    {

    }

    void IFSMState.OnEnter()
    {
        throw new System.NotImplementedException();
    }

    void IFSMState.OnUpdate(Character character, ICommand Command)
    {
        throw new System.NotImplementedException();
    }

    void IFSMState.Exit()
    {
        throw new System.NotImplementedException();
    }
}
