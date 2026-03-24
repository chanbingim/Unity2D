using UnityEngine;

public class Player : Character
{
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        m_fSpeed = 10;
        m_Health = 1000;
        m_Character_Fsm = PlayerFSM.CreateFSM();
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
