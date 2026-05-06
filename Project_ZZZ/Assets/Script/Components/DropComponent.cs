using System.Collections.Generic;
using System.Linq;
using UnityEngine;

[CreateAssetMenu(
    fileName = "DropComponent",
    menuName = "ScriptableObjects/DropComponent",
    order = 1)]
public class DropComponent : ScriptableObject
{
    [System.Serializable]
    private struct DropData
    {
        public long     lWeight;
        public int      iIndex;
    }

    [SerializeField] List<DropData> m_DropList = new List<DropData>();
    List<(float, int)> m_Candidates = new List<(float, int)>();

    void Awake()
    {
        long TotalWeight = m_DropList.Sum(data => data.lWeight);
        foreach (DropData data in m_DropList) {
            m_Candidates.Add((data.lWeight / TotalWeight, data.iIndex));
        }

        m_Candidates.Sort(((float, int) src, (float, int) dest) => {
            return src.Item1.CompareTo(dest.Item1);
        });
    }

    public int Get_DropItemIndex()
    {
        Random.InitState((int)System.DateTime.Now.Ticks);
        double Pivot = Random.Range(0f, 1f);
        double acc = 0;

        foreach ((float, int) data in m_Candidates)
        {
            acc += data.Item1;
            if (Pivot <= acc)
                return data.Item2;
        }

        return -1;
    }

}
