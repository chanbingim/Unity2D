using GameFSM;
using InputCommand;
using UnityEngine;

public class IdleState : IFSMState<PlayerFSM.ANIM_STATE>
{
    PlayerFSM.ANIM_STATE IFSMState<PlayerFSM.ANIM_STATE>.Type => PlayerFSM.ANIM_STATE.IDLE;
    public int IgnoreType => 0;

    public IdleState()
    {

    }

    void IFSMState.OnEnter()
    {

    }

    void IFSMState.OnUpdate(Character character, ICommand Command)
    {
        character.Idle();
    }
    
    void IFSMState.Exit()
    {

    }
}
