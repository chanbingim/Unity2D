using UnityEngine;

public class RewordBox : WorldObject
{
    [SerializeField] private DropComponent  m_DropComponent;
    [SerializeField] private float          m_fDeadDelay;

    private Animator        m_Animator = null;
    private bool            m_bIsOpen = false;

    void Awake()
    {
        m_Animator = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    #region Public
    public void Open_RewordBox()
    {
        m_bIsOpen = true;
        // Play Animation
    }

    public void DropReword()
    {
        // Play Animation
    }

    public void Dead_RewordBox()
    {
        Destroy(gameObject, m_fDeadDelay);
    }
    #endregion
}
