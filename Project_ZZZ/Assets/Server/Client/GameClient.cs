using ClientToServer;
using ServerToClient;

using InputCommand;
using Nettention.Proud;
using UnityEngine;
using System.Collections.Generic;

public class GameClient : MonoBehaviour
{
    Dictionary<int, GameObject>     m_Players;
    [SerializeField]    int         m_MyID;
    public GameObject               m_PlayerPrefab;

    NetClient       m_netClient = null;
    Stub            m_ClientStub = null;
    Proxy           m_ClientProxy = null;

    void Start()
    {
        m_netClient = new NetClient();
        // 파라미터 정의
        NetConnectionParam ClientParam = new NetConnectionParam();
        m_Players = new Dictionary<int, GameObject>();

        // 서버와 동일한 protocol version, 입력하지 않아도 됨
        //cp.protocolVersion.Set(version);
        // server address
        ClientParam.serverIP = "localhost";
        // server port
        ClientParam.serverPort = 33334;

        InitalizedClient();
        m_netClient.Connect(ClientParam);
    }

    void Update()
    {
        m_netClient.FrameMove();
    }

    private void LateUpdate()
    {
        
    }

    private void OnDestroy()
    {
        m_netClient.Disconnect();
    }

    public void SendMessage(HostID iD = 0)
    {
        //if(0 == iD)
            //netClient.SendUserMessage(netClient.GetLocalHostID(), RmiContext::Unreliable, data, 100););
    }

    public void ClientMoveMessage(ICommand Command)
    {
        if(null != Command)
        {
            CMoveCommand moveCommand = (CMoveCommand)Command;
            Vector3 CurPos = moveCommand.m_Transform.position;
            Vector3 NewDir = moveCommand.m_vDir * moveCommand.m_fSpeed * Time.deltaTime;

            m_ClientProxy.OnPositionUpdated(HostID.HostID_Server, RmiContext.UnreliableSend, (int)m_MyID,
                   CurPos.x, CurPos.y, CurPos.z, NewDir.x, NewDir.y, NewDir.z);
        }
    }

    private bool OnOtherPlayerUpdated(HostID remote, RmiContext rmiContext, int clientId, string NickName, float px, float py, float pz)
    {
        GameObject pNewPlayer = null;
        if (m_Players.ContainsKey(clientId))
        {
            pNewPlayer = m_Players[clientId];
        }
        else
        {
            pNewPlayer = GameObject.Instantiate(m_PlayerPrefab);
            if(clientId == m_MyID)
                pNewPlayer.name = "Player";
            else
                pNewPlayer.name = "other" + clientId;

            m_Players.Add(clientId, pNewPlayer);
        }

        pNewPlayer.transform.position = new Vector3(px, py, pz);

        return true;
    }

    private bool OnPlayerJoined(HostID remote, RmiContext rmiContext, int clientId, float px, float py, float pz)
    {
        m_MyID = clientId;
        gameObject.transform.position = new Vector3(px, py, pz);
        return true;
    }

    private bool OnPositionUpdated(HostID remote, RmiContext rmiContext, int clientId, float px, float py, float pz, float dx, float dy, float dz)
    {
        if (m_Players.ContainsKey(clientId))
        {
            GameObject pNewPlayer = m_Players[clientId];
            pNewPlayer.transform.position = new Vector3(px, py, pz); // Vector3.Lerp(pNewPlayer.transform.position, new Vector3(px, py, pz), Time.deltaTime);
        }

        return true;
    }

    private bool OnChat(HostID remote, RmiContext rmiContext, int ClienID, string Message)
    {
        Debug.Log("ClienID : " + ClienID);
        Debug.Log("ClienID : " + Message);
        return true;
    }

    #region Private

    private void InitalizedClient()
    {
        BindNetClientHandler();
        InitializedSutb();
        InitializedProxy();
    }

    private void BindNetClientHandler()
    {
        m_netClient.JoinServerCompleteHandler = OnServerJoinComplete;
    }

    private void InitializedSutb()
    {
        m_ClientStub = new Stub();
        m_ClientStub.OnPositionUpdated += OnPositionUpdated;
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
