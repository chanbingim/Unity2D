using GameFSM;
using InputCommand;
using UnityEngine;

public class ATKState : IFSMState<PlayerFSM.ANIM_STATE>
{
    PlayerFSM.ANIM_STATE IFSMState<PlayerFSM.ANIM_STATE>.Type => PlayerFSM.ANIM_STATE.ATTACK;
    public int IgnoreType => 0;

    public ATKState()
    {

    }

    void IFSMState.OnEnter()
    {

    }

    void IFSMState.OnUpdate(Character character, ICommand Command)
    {
        character.Attack();
    }
    
    void IFSMState.Exit()
    {

    }
}
