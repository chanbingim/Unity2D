using ClientToServer;
using ServerToClient;

using InputCommand;
using Nettention.Proud;
using UnityEngine;
using System.Collections.Generic;
using System;
using static Defines;

public class GameClient : MonoBehaviour
{
    public GameObject                   m_PlayerPrefab;
    public event Action<string>         m_ChatEvent;

#region private
    private static GameClient m_pInstance = null;
    private NetClient           m_netClient = null;
    private Stub                m_ClientStub = null;
    private Proxy               m_ClientProxy = null;

    [SerializeField] private int                m_MyID;
    private Dictionary<int, Player_Controller>  m_Players;
    #endregion
    private void Awake()
    {
        if (null == m_pInstance)
        {
            m_pInstance = this;
            if (RESULT.FAIL == m_pInstance.InitalizedClient())
            {
                Destroy(m_pInstance);
            }
        }
    }

    public static GameClient Get_Instance()
    {
        return m_pInstance;
    }

    void Update()
    {
        if (null != m_netClient)
            m_netClient.FrameMove();
    }

    private void LateUpdate()
    {
        
    }

    private void OnDestroy()
    {
        m_netClient.Disconnect();
    }

    public void Send_Message(String text)
    {
        m_ClientProxy.OnChat(HostID.HostID_Server, RmiContext.ReliableSend, m_MyID, text);
    }

    public void ClientMoveMessage(ICommand Command)
    {
        if(null != Command)
        {
            CMoveCommand moveCommand = (CMoveCommand)Command;
            Vector3 CurPos = moveCommand.m_vCurPos;
            Vector3 NewDir = moveCommand.m_vDir * moveCommand.m_fSpeed * Time.deltaTime;

            m_ClientProxy.OnPositionUpdated(HostID.HostID_Server, RmiContext.UnreliableSend, (int)m_MyID,
                   CurPos.x, CurPos.y, CurPos.z, NewDir.x, NewDir.y, NewDir.z);
        }
    }

    private bool OnOtherPlayerUpdated(HostID remote, RmiContext rmiContext, int clientId, string NickName, float px, float py, float pz)
    {
        Player_Controller pController = null;
        if (m_Players.ContainsKey(clientId))
        {
            pController = m_Players[clientId];
            pController.Update_Position(px, py, pz);
        }
        else
        {
            GameObject pNewPlayer = GameObject.Instantiate(m_PlayerPrefab);
            if(clientId == m_MyID)
                pNewPlayer.name = "Player";
            else
                pNewPlayer.name = "other" + clientId;

            m_Players.Add(clientId, pNewPlayer.GetComponent<Player_Controller>());
        }
        
        return true;
    }

    private bool OnPlayerJoined(HostID remote, RmiContext rmiContext, int clientId, float px, float py, float pz)
    {
        m_MyID = clientId;
        gameObject.transform.position = new Vector3(px, py, pz);
        return true;
    }

    private bool OnChat(HostID remote, RmiContext rmiContext, int ClienID, string Message)
    {
        m_ChatEvent.Invoke(Message);
        return true;
    }

#region Private
    private RESULT InitalizedClient()
    {
        m_netClient = new NetClient();
        // 파라미터 정의
        NetConnectionParam ClientParam = new NetConnectionParam();
        m_Players = new Dictionary<int, Player_Controller>();

        // 서버와 동일한 protocol version, 입력하지 않아도 됨
        //cp.protocolVersion.Set(version);
        // server address
        ClientParam.serverIP = "localhost";
        // server port
        ClientParam.serverPort = 33334;
      
        BindNetClientHandler();
        InitializedSutb();
        InitializedProxy();

        m_netClient.Connect(ClientParam);
        return RESULT.SUCCESS;
    }

    private void BindNetClientHandler()
    {
        m_netClient.JoinServerCompleteHandler = OnServerJoinComplete;
    }

    private void InitializedSutb()
    {
        m_ClientStub = new Stub();
        m_ClientStub.OnChat += OnChat;
        m_ClientStub.OnPlayerJoined += OnPlayerJoined;
        m_ClientStub.OnOtherPlayerUpdated += OnOtherPlayerUpdated;

        m_netClient.AttachStub(m_ClientStub);
    }

    private void InitializedProxy()
    {
        m_ClientProxy = new Proxy();
        m_netClient.AttachProxy(m_ClientProxy);
    }

    void OnServerJoinComplete(ErrorInfo info, ByteArray replyFromServer)
    {
        if(info.errorType == ErrorType.Ok)
            Debug.Log("Player Join");
        else
            Debug.Log("Player Join Fail");
    }
#endregion

}
