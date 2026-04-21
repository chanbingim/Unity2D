using GameFSM;
using InputCommand;
using UnityEngine.TextCore.Text;

public class IdleState : IFSMState<PlayerFSM.ANIM_STATE>
{
    public PlayerFSM.ANIM_STATE Type => PlayerFSM.ANIM_STATE.IDLE;
    public IdleState()
    {

    }

    public void OnEnter()
    {

    }

    public void OnUpdate(Character character, ICommand Command)
    {
        character.Idle();
    }
    
    public void Exit()
    {

    }
}
