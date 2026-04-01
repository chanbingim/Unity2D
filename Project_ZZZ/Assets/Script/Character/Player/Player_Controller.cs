using InputCommand;
using UnityEditor.PackageManager;
using UnityEngine;

public class Player_Controller : CCharacter_Controller
{
   
    [SerializeField] Character      m_Character = null;
    [SerializeField] Player_Camera  m_PlayerCam = null;

    private CMoveCommand        m_MoveCommand;
    private GameClient          m_Client = null;

    void Start()
    {
        m_Client = gameObject.GetComponent<GameClient>();
        m_MoveCommand = new CMoveCommand(m_Character.transform, Vector3.zero, 0.0f, 0.0f);
    }

    // Update is called once per frame
    void Update()
    {
        if (null != m_Character)
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

                m_MoveCommand.m_vDir = vDir.x * camRight + vDir.z * camForward;
                m_MoveCommand.m_fSpeed = m_Character.m_fSpeed;
                m_MoveCommand.m_fRotSpeed = m_Character.m_fRotationSpeed;
                m_Client.ClientMoveMessage(m_MoveCommand);

                //m_Character.HandleCommand("Move", m_MoveCommand);
            }
            else
                m_Character.HandleCommand("Idle", null);
        }
    }
}
