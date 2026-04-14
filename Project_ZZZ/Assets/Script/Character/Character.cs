using InputCommand;
using UnityEngine;

public abstract class Actor : MonoBehaviour
{
    protected Transform     m_Transform = null;
    protected Animator      m_Animator = null;
}

public abstract class Character : Actor
{
    public float m_fRotationSpeed { get; set; }
    public float m_fSpeed { get; set; }
    public float m_Health { get; set; }

    [SerializeField] protected Fsm      m_Character_Fsm = null;
    [SerializeField] protected string   m_CurStateName = "";

    public abstract void HandleCommand(string StateName, CBaseCommand command);

    public virtual void Move(Vector3 dir)
    {
        m_Transform.position = dir;
    }

    public virtual void Idle() { }
    public virtual void Attack() { }
}
