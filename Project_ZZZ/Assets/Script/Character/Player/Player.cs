using InputCommand;
using UnityEngine;

public class Player : Character
{
    public delegate void OnEnter(Transform transform);
    public OnEnter TirggerEnter;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        m_fSpeed = 10;
        m_Health = 1000;
        m_fRotationSpeed = 3;
        m_Character_Fsm = PlayerFSM.CreateFSM();
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

}
