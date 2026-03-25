using UnityEngine;
using UnityEngine.UIElements;
using static UnityEngine.GraphicsBuffer;

public class InteractionUI : MonoBehaviour
{
    public GameObject   m_Pannel;      // Canvas æ»¿« UI
    public GameObject   Player;
    public Vector2      m_Offset;
    private Camera      m_MainCam;

    void Start()
    {
        Player.GetComponent<Player>().TirggerEnter += Interaction_Enable;
        m_MainCam = Camera.main;
        gameObject.SetActive(false);
    }

    void Update()
    {
        
    }

    public void Interaction_Enable(Transform PlayerTransform)
    {
        if(null == PlayerTransform)
            gameObject.SetActive(false);
        else
        {
            gameObject.SetActive(true);
            Vector3 screenPos = m_MainCam.WorldToScreenPoint(PlayerTransform.position);
            transform.position = screenPos;
        }
    }
}
