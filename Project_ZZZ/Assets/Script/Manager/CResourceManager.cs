using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.SceneManagement;

public class CResourceManager : MonoBehaviour
{
    [System.Serializable]
    public class PrefabEntry
    {
        public string       Key;
        public GameObject   Value;
    }
    [SerializeField] private List<PrefabEntry>      m_PrefabList = new List<PrefabEntry>();
     private Dictionary<string, GameObject>         m_Prefabs = new Dictionary<string, GameObject>();

    void Update()
    {
        
    }

    public GameObject Get_Prefab(string key)
    {
        GameObject prefab = null;
        m_Prefabs.TryGetValue(key, out prefab);

        return prefab;
    }


    #region Private
    private void Initialize()
    {
        m_Prefabs = m_PrefabList.ToDictionary(x => x.Key, x => x.Value);
    }
    #endregion

    #region SingleTon
    static CResourceManager        m_pInstance = null;
    public static CResourceManager Get_Instance() { return m_pInstance; }

    void Awake()
    {
        if (null == m_pInstance)
        {
            m_pInstance = this;
            m_pInstance.Initialize();
            DontDestroyOnLoad(m_pInstance);
            Debug.Log("Create Game Manager");
        }
        else
            Destroy(m_pInstance);
    }

    #endregion
}
