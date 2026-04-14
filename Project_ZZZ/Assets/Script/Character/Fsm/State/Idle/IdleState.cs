using GameFSM;
using InputCommand;
using UnityEngine.TextCore.Text;

public class IdleState : IFSMState
{
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
