using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Device;

public class InteractorComponent : MonoBehaviour
{
    private List<GameObject>    m_pTargetList = new List<GameObject>();
    private GameObject          m_pTarget = null;

    private void Update()
    {
        // 매프레임 거리순서로 정렬을 진행한다.
        // 가장 가까운녀석이랑 상호작용느낌 일단은 이런식으로
        Vector3 OwnerPos = gameObject.transform.position;

        if (1 < m_pTargetList.Count)
        {
            m_pTargetList.Sort((GameObject Src, GameObject Dest) => {

                float SrcLength = Vector3.Magnitude(OwnerPos - Src.transform.position);
                float DestLength = Vector3.Magnitude(OwnerPos - Dest.transform.position);

                return SrcLength.CompareTo(DestLength);
            });
        }

        if (0 < m_pTargetList.Count)
            m_pTarget = m_pTargetList[0];
        else
            m_pTarget = null;
    }

    #region Public
    public void TryInteract()
    {
        if (m_pTarget)
        {
            InteractableComponent InteractableCom = m_pTarget.GetComponent<InteractableComponent>();
            InteractableCom.OnInteract(this);
        }
    }
    #endregion

    #region Private
    private void OnTriggerEnter(Collider other)
    {
        m_pTargetList.Add(other.gameObject);
    
       
    }

    private void OnTriggerExit(Collider other)
    {
        m_pTargetList.Remove(other.gameObject);
    }
    #endregion
}
