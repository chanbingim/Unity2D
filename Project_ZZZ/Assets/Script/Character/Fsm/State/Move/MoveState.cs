using GameFSM;
using System;
using Unity.VisualScripting;
using UnityEngine;

public class MoveState : IFSMState
{
    Transform m_Transform = null;
    float m_fMoveSpeed = 0.0f;

    MoveState(Transform transform, float Speed)
    {

    }

    public void OnEnter()
    {

    }

    public void OnUpdate()
    {

    }

    public void Exit()
    {

    }

    public void Move(Vector3 dir)
    {
        m_Transform.position += dir * Time.deltaTime * m_fMoveSpeed;
    }
}
