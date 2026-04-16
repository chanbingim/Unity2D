using InputCommand;
using System;
using Unity.VisualScripting;
using UnityEngine;

public class Player_Controller : CCharacter_Controller
{
   
    [SerializeField] Player         m_Character = null;
    [SerializeField] Player_Camera  m_PlayerCam = null;

    private Boolean             m_EnableChating = false;
    private CMoveCommand        m_MoveCommand;
    private GameClient          m_Client = null;

    void Start()
    {
        m_Client = GameClient.Get_Instance();
        if(gameObject.name == "Player")
        {
            m_PlayerCam = Camera.main.GetComponent<Player_Camera>();
            m_PlayerCam.Target = m_Character.gameObject;
        }

        GameManager.Get_Instance().Add_ListenList(EnableChating);
        m_MoveCommand = new CMoveCommand(Vector3.zero, Vector3.zero, 0.0f);
    }

    // Update is called once per frame
    void Update()
    {
        if (null != m_Character)
        {
            if(false == m_EnableChating)
                InputFocusCharacter();
        }
    }
    
    private void InputFocusCharacter()
    {
        if (false == m_EnableChating)
        {
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

                m_MoveCommand.m_vCurPos = gameObject.transform.position;
                m_MoveCommand.m_vDir = vDir.x * camRight + vDir.z * camForward;
                m_MoveCommand.m_fSpeed = m_Character.m_fSpeed;

                m_Character.Character_LookAt(m_MoveCommand.m_vDir);
                m_Client.ClientMoveMessage(m_MoveCommand);
            }
        }
    }

    public void EnableChating(Boolean bIsEnable)
    {
        m_EnableChating = bIsEnable;
    }

    public  void Update_Position(float px, float py, float pz)
    {
        m_MoveCommand.m_vDir = new Vector3(px, py, pz);

        if (m_MoveCommand.m_vDir != m_Character.transform.position)
        {
            m_Character.HandleCommand("Move", m_MoveCommand);
        }
        else
        {
            m_Character.HandleCommand("Idle", null);
        }
    }
}
