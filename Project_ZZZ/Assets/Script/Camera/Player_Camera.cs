using UnityEngine;
using static UnityEngine.GraphicsBuffer;

public class Player_Camera : MonoBehaviour
{
    enum CAMERA_MODE { TOP_VIEW, END };

    public GameObject       Target;
    public float            m_fSensitive;
    public float            m_fCamDistance;
    Vector2                 m_Angle;
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {   
        
    }

    // Update is called once per frame
    void Update()
    {
        m_Angle.x -= Input.GetAxis("Mouse Y") * m_fSensitive;
        m_Angle.y += Input.GetAxis("Mouse X") * m_fSensitive;
        m_Angle.x = Mathf.Clamp(m_Angle.x, -30f, 45f);

        float CamDistance = m_fCamDistance;
        if (m_Angle.x < 0)
            CamDistance = Mathf.Lerp(m_fCamDistance, 5, m_Angle.x / -30f);

        // 타겟 기준으로 공전 위치 계산
        Quaternion rot = Quaternion.Euler(m_Angle.x, m_Angle.y, 0f);
        transform.position = Target.transform.position + rot * new Vector3(0, 0, -CamDistance);
        transform.LookAt(Target.transform.position);  // 공전이면 LookAt 유효
    }
}
