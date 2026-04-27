using GameFSM;
using InputCommand;
using UnityEngine;

public class MoveState : IFSMState<PlayerFSM.ANIM_STATE>
{
    PlayerFSM.ANIM_STATE IFSMState<PlayerFSM.ANIM_STATE>.Type => PlayerFSM.ANIM_STATE.MOVE;
    public MoveState()
    {

    }

    void IFSMState.OnEnter()
    {

    }

    void IFSMState.OnUpdate(Character character, ICommand Command)
    {
        CMoveCommand moveCommand = Command as CMoveCommand;
        Vector3 Dir = moveCommand.m_vDir * moveCommand.m_fSpeed * Time.deltaTime;

        character.Move(Dir);
    }

    void IFSMState.Exit()
    {

    }
}
