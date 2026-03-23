using UnityEngine;

public class Character : MonoBehaviour
{
    [SerializeField]
    Fsm Character_Fsm = null;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        Character_Fsm = new Fsm();
    }

    // Update is called once per frame
    void Update()
    {
        if (null != Character_Fsm)
            Character_Fsm.FSM_Update();



    }
}
