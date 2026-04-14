using InputCommand;
using UnityEngine;

public class Player : Character
{
    public delegate void OnEnter(Transform transform);
    public OnEnter      TirggerEnter;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        m_fSpeed = 10;
        m_Health = 1000;
        m_fRotationSpeed = 3;
        m_Character_Fsm = PlayerFSM.CreateFSM();

        m_Transform = gameObject.transform;
        m_Animator = gameObject.GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
    }

    public void Character_LookAt(Vector3 vDir)
    {
        Quaternion NewRot = Quaternion.LookRotation(vDir);
        transform.rotation = Quaternion.Lerp(
            transform.rotation, NewRot, m_fSpeed * Time.deltaTime);
    }

    private void OnTriggerEnter(Collider other)
    {
        Debug.Log("Player Trigger Enter");
        TirggerEnter.Invoke(transform);
    }

    private void OnTriggerExit(Collider other)
    {
        Debug.Log("Player Trigger Exit");
        TirggerEnter.Invoke(null);
    }

    public override void Idle()
    {
        m_Animator.SetFloat("Velocity", 0f);
    }

    public override void Move(Vector3 dir)
    {
        m_Animator.SetFloat("Velocity", 1f);
        base.Move(dir);
    }

    public override void Attack()
    {

    }

    public override void HandleCommand(string StateName, CBaseCommand command)
    {
        if (null != m_Character_Fsm)
        {
            if (m_CurStateName != StateName)
            {
                m_CurStateName = StateName;
                m_Character_Fsm.Change_State(StateName);
            }

            m_Character_Fsm.FSM_Update(this, command);
        }
    }
}
