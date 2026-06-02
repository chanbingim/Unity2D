using InputCommand;
using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Events;

public class Player_Controller : CCharacter_Controller
{
    [SerializeField] Player         m_Character = null;
    [SerializeField] Player_Camera  m_PlayerCam = null;

    [SerializeField] UnityEvent     m_InteractionEvent;


    Dictionary<string, ICommand>    m_Commands = new Dictionary<string, ICommand>();

    private Boolean             m_EnableChating = false;
    private Boolean             m_DisableInput = false;

    private GameClient          m_Client = null;

    void Start()
    {
        m_Client = GameClient.Get_Instance();
        if(gameObject.name == "Player")
        {
            m_PlayerCam = Camera.main.GetComponent<Player_Camera>();
            m_PlayerCam.Target = m_Character.gameObject;
            m_DisableInput = true;
        }

        ADD_CommandList();
        GameManager.Get_Instance().Add_ListenList(EnableChating);
    }

    // Update is called once per frame
    void Update()
    {
        if (null != m_Character)
        {
            if(false == m_EnableChating && m_DisableInput)
                InputFocusCharacter();
        }
    }

    public void EnableChating(Boolean bIsEnable)
    {
        m_EnableChating = bIsEnable;
    }

    public void Update_Transform(Vector3 vScale, Quaternion vRot, Vector3 vPos)
    {
        m_Character.transform.localScale = vScale;
        m_Character.transform.rotation = vRot;
        Update_Position(vPos.x, vPos.y, vPos.z);
    }

    void Update_Position(float px, float py, float pz)
    {
        CMoveCommand MoveCommand = m_Commands["Move"] as CMoveCommand;
        if (null == MoveCommand)
            return;

        MoveCommand.m_vDir = new Vector3(px, py, pz);
        Vector3 diff = m_Character.transform.position - MoveCommand.m_vDir;
        if (diff.sqrMagnitude > 0.5f * 0.5f)
        {
            m_Character.transform.position = MoveCommand.m_vDir;
        }
    }

    #region Private
    private bool ADD_CommandList()
    {
        m_Commands.Add("Move", new CMoveCommand(Vector3.zero, Vector3.zero, 0.0f));
        m_Commands.Add("Attack", new CATK_Command(50f, 5f));

        return true;
    }

    private void InputFocusCharacter()
    {
        if (false == m_EnableChating)
        {
            if(Input.GetKeyDown(KeyCode.Mouse0))
                Input_Attack();

            if (Input.GetKeyDown(KeyCode.K))
                m_InteractionEvent.Invoke();

            Input_Move();
        }
    }

    private void Input_Move()
    {
        CMoveCommand MoveCommand = m_Commands["Move"] as CMoveCommand;
        if (null == MoveCommand)
            return;

        Vector3 vDir = new Vector3(Input.GetAxis("Horizontal"), 0.0f, Input.GetAxis("Vertical"));
        if (Vector3.zero != vDir)
        {
            // Y를 제거한 x z로 Target 위치 - 카메라 위치 = Look Vector;
            // 카메라 기준으로 Look 과 Right를 가져와서 이동시킨다.
            Vector3 camForward = m_PlayerCam.transform.forward;
            Vector3 camRight = m_PlayerCam.transform.right;

            camRight.y = camForward.y = 0f;
            camForward.Normalize();
            camRight.Normalize();

            MoveCommand.m_vCurPos = m_Character.transform.position;
            MoveCommand.m_vDir = vDir.x * camRight + vDir.z * camForward;
            MoveCommand.m_vDir = MoveCommand.m_vDir.normalized;
            MoveCommand.m_fSpeed = m_Character.m_fSpeed;

            m_Character.Character_LookAt(MoveCommand.m_vDir);
            m_Character.HandleCommand("Move", MoveCommand);
            m_Client.ClientMoveMessage(MoveCommand);
        }
        else
        {
            m_Character.HandleCommand("Idle", null);
        }
    }

    private void Input_Attack()
    {
        CATK_Command ATKCommand = m_Commands["Attack"] as CATK_Command;
        if (null == ATKCommand)
            return;

        ATKCommand.m_fATK_Damage = 50;
        ATKCommand.m_fATK_Speed = 5;
        m_Character.HandleCommand("Attack", ATKCommand);

    }
    #endregion
}
