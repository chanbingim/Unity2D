using GameFSM;
using System.Collections.Generic;
using UnityEngine;

public class PlayerFSM : Fsm
{
    public enum ANIM_STATE : int { IDLE, MOVE, ATTACK, HIT, END };

    public ANIM_STATE CurState => m_CurAnimState;
    public ANIM_STATE PreState => m_PreAnimState;

    ANIM_STATE m_CurAnimState = ANIM_STATE.IDLE;
    ANIM_STATE m_PreAnimState = ANIM_STATE.END;

    public static PlayerFSM CreateFSM()
    {
        PlayerFSM FSM = new PlayerFSM();
        if (FSM.Initalize())
            return FSM;

        return null;
    }

    public override void Change_State(string StateName)
    {
        IFSMState<ANIM_STATE> AnimState = m_CurState as IFSMState<ANIM_STATE>;
        m_PreAnimState = AnimState.Type;

        base.Change_State(StateName);

        AnimState = m_CurState as IFSMState<ANIM_STATE>;
        m_CurAnimState = AnimState.Type;
    }

    private bool Initalize()
    {
        Dic_State = new Dictionary<string, IFSMState>();
        Dic_State.Add("Move", new MoveState());
        Dic_State.Add("Idle", new IdleState());

        return true;
    }

    private PlayerFSM() {}
}
