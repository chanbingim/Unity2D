using NUnit.Framework.Constraints;
using UnityEngine;
using static UnityEngine.GraphicsBuffer;

public class Player_Controller : CCharacter_Controller
{
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        Vector3 input = new Vector3(Input.GetAxis("Horizontal"), 0.0f, Input.GetAxis("Vertical"));

        transform.position += input * Time.deltaTime * 10.0f;
        transform.forward = input.normalized;
    }
}
