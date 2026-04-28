using GameFSM;
using InputCommand;
using System.Collections.Generic;
using UnityEditor.MPE;
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

    public override void FSM_Update(Character character, CBaseCommand command)
    {
        base.FSM_Update(character, command);
        m_GameClient.UpdateAnimation((int)m_CurAnimState, 0);
    }

    public override void Change_State(string StateName)
    {
        IFSMState<ANIM_STATE> AnimState = m_CurState as IFSMState<ANIM_STATE>;
        if (null != AnimState)
            m_PreAnimState = AnimState.Type;

        base.Change_State(StateName);

        AnimState = m_CurState as IFSMState<ANIM_STATE>;
        m_CurAnimState = AnimState.Type;
        
    }

    private bool Initalize()
    {
        m_GameClient = GameClient.Get_Instance();
        Dic_State.Add("Move", new MoveState());
        Dic_State.Add("Idle", new IdleState());
        Dic_State.Add("Attack", new ATKState());
        return true;
    }

    private PlayerFSM() {}
}
