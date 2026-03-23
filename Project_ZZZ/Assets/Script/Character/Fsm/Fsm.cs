using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.Events;

public class Fsm
{
    [SerializeField]
    private float m_fMoveSpeed;
    private Vector3 m_fDirection;

    // 상태 만들고 상태안에서 이동움직임 처리하자

    public Vector3 Get_Direction() { return m_fDirection; }

    public void Horizontal_Move(float fValue)
    {
        Debug.Log("캐릭터 가로 이동");
    }

    public void Vertical_Move(float fValue)
    {
        Debug.Log("캐릭터 세로 이동");
    }
}
