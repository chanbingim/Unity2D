using GameFSM;
using System.Collections.Generic;
using UnityEngine;

public class PlayerFSM : Fsm
{
    public static PlayerFSM CreateFSM()
    {
        PlayerFSM FSM = new PlayerFSM();
        if (FSM.Initalize())
            return FSM;

        return null;
    }

    private bool Initalize()
    {
        Dic_State = new Dictionary<string, IFSMState>();
        Dic_State.Add("Move", new MoveState());
        return true;
    }

    private PlayerFSM() { }
}
