using System;
using Unity.VisualScripting;
using UnityEngine;

public class MoveState : IState, IMovement
{
    [System.Serializable]
    Transform m_Transform = null;

    [System.Serializable]
    float m_fMoveSpeed = 0.0f;


    MoveState()
    {

    }

    public OnEnter()
    {

    }

    public OnUpdate()
    {

    }

    public Exit()
    {

    }

    public void Move(Vector3 dir)
    {
        m_Transform.position += dir * Time.deltaTime * m_fMoveSpeed;
    }
}
