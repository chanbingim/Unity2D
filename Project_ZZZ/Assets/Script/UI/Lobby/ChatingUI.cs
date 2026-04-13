using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
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

    [SerializeField] private List<String>       m_ChatingText;
    [SerializeField] private InputField         m_InputField = null;
    [SerializeField] private List<GameObject>   m_ViewList;
    [SerializeField] private Scrollbar          m_Scrollbar = null;

    private GameClient                          m_Client = null;
    private int                                 m_ViewBoundIdx = 0;
    private Vector2                             m_PrefabSize = Vector2.zero;
    private Coroutine                           m_HideRoutine;

    // Start is called once before the first execution of Update after the MonoBehaviour is created
    void Start()
    {
        gameObject.SetActive(false);
        m_ChatingText = new List<String>();
        if(null != m_ViewPrefab)
        {
            RectTransform ParentRectTransform = GetComponent<RectTransform>();
            RectTransform PrefabRectTransform = m_ViewPrefab.GetComponent<RectTransform>();
            m_PrefabSize = new Vector2((ParentRectTransform.rect.width - 10.0f) * 0.5f, ParentRectTransform.rect.height / m_ViewChatList);

            for (int i = 0; i < m_ViewChatObject; ++i)
            {
                m_ViewList.Add(GameObject.Instantiate(m_ViewPrefab, gameObject.transform));
                m_ViewList[i].SetActive(false);

                PrefabRectTransform = m_ViewList[i].GetComponent<RectTransform>();
                PrefabRectTransform.sizeDelta = new Vector2(m_PrefabSize.x * 2.0f, m_PrefabSize.y);
                PrefabRectTransform.anchoredPosition = new Vector3(m_PrefabSize.x, -((i * m_PrefabSize.y) + m_PrefabSize.y * 0.5f), 0.0f);
            }
        }

        GameManager.GetInstance().Add_ListenList(Enable_Chating);
        Refesh_ChatingView(0.0f);

        m_Scrollbar.onValueChanged.AddListener(Refesh_ChatingView);
        m_Client = GameClient.Get_Instance();
        m_Client.m_ChatEvent += BoardCastChatingMessage;
    }

    // Update is called once per frame
    void Update()
    {
       for (int i = 0; i < m_ViewChatObject; ++i)
       {
           if (m_ViewBoundIdx + i < m_ChatingText.Count)
           {
               m_ViewList[i].SetActive(true);
               m_ViewList[i].GetComponent<Text>().text = m_ChatingText[m_ViewBoundIdx + i];
           }
       }

       if(Input.GetKeyDown(KeyCode.Escape))
       {
            for(int i = 0; i< 10; ++i)
                m_ChatingText.Add("Test" + i);

            m_Scrollbar.value = 1.0f;
       }
    }

    private void Enable_Chating(Boolean bIsEnable)
    {
        if(bIsEnable)
        {
            gameObject.SetActive(true);
            m_InputField.Select();

            if(null != m_HideRoutine)
                StopCoroutine(m_HideRoutine);        
        }
        else
            m_HideRoutine = StartCoroutine(HideChatAfterDelay(3f));
    }

    IEnumerator HideChatAfterDelay(float time)
    {
        yield return new WaitForSeconds(time);
        gameObject.SetActive(false);
    }

    public void Refesh_ChatingView(float Value)
    {
        // 여기서 슬라이드 바 위치를 받아서 데이터를 뿌린다.
        int maxStartIndex = m_ChatingText.Count - m_ViewChatList;

        if (maxStartIndex < 0)
            m_ViewBoundIdx = 0;
        else
            m_ViewBoundIdx = Mathf.Clamp(Mathf.FloorToInt(Value * maxStartIndex), 0, maxStartIndex);
    }

    public void EditEndText()
    {
        if("" != m_InputField.text)
        {
            m_Client.Send_Message(m_InputField.text);
            m_InputField.text = "";
        }
    }

    public void BoardCastChatingMessage(String  Message)
    {
        m_ChatingText.Add(Message);
        if (m_Scrollbar.value >= 0.9f)
            Refesh_ChatingView(1.0f);
    }
}
