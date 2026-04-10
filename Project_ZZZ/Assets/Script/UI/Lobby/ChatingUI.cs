using System;
using System.Collections;
using System.Collections.Generic;
using UnityEditor.PackageManager;
using UnityEngine;
using UnityEngine.UI;

public class ChatingUI : MonoBehaviour
{
    // 슬라이드를 통해 Chating을 스크롤바를 통해 확인하고
    // 스크롤바 업데이트에서만 채팅을 변경한다.
    [SerializeField] private int            m_ViewChatList = 5;
    [SerializeField] private int            m_ViewChatObject = 5;
    [SerializeField] private GameObject     m_ViewPrefab = null;

    private List<GameObject>                m_ViewList;
    private List<String>                    m_ChatingText;
    private GameClient                      m_Client = null;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        m_ChatingText = new List<String>();
        if(null != m_ViewPrefab)
        {
            for (int i = 0; i < m_ViewChatObject; ++i)
                m_ViewList.Add(GameObject.Instantiate(m_ViewPrefab));
        }

        m_Client = GameClient.Get_Instance();
        m_Client.m_ChatEvent += BoardCastChatingMessage;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void Refesh_ChatingView()
    {
        // 여기서 슬라이드 바 위치를 받아서 데이터를 뿌린다.
    }

    public void EditEndText(String  text)
    {
        m_Client.SendMessage(text);
    }

    public void BoardCastChatingMessage(String  Message)
    {
        m_ChatingText.Add(Message);
    }
}
