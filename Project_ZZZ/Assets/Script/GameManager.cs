using UnityEngine;

public class GameManager : MonoBehaviour
{
    CUtilyManager m_gUtilyMgr = null;
    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Awake()
    {
        m_gUtilyMgr = CUtilyManager.Get_Instance();
        Debug.Log("Create Manager");

    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
