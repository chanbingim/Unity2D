using NUnit.Framework.Constraints;
using UnityEngine;

public class Player_Controller : MonoBehaviour
{
    [SerializeField]
    Fsm PlayerFsm = null;

    void Start()
    {
        PlayerFsm = new Fsm();
    }

    // Update is called once per frame
    void Update()
    {
        if(null != PlayerFsm)
        {
            if(Input.GetKeyDown(KeyCode.RightArrow))
                PlayerFsm.Horizontal_Move(1);

            if (Input.GetKeyDown(KeyCode.LeftArrow))
                PlayerFsm.Horizontal_Move(-1);

            if (Input.GetKeyDown(KeyCode.UpArrow))
                PlayerFsm.Vertical_Move(1);

            if (Input.GetKeyDown(KeyCode.DownArrow))
                PlayerFsm.Vertical_Move(-1);
        }
    }
}
