using ClientToServer;
using ServerToClient;

using InputCommand;
using Nettention.Proud;
using UnityEngine;
using System.Collections.Generic;
using System;
using static Defines;
using Client_Structs;

public class GameClient : MonoBehaviour
{
    public ServerLoginEventHandler      ServerLoginHandler = new ServerLoginEventHandler();
    public ServerChatEventHandler       ServerChatHandler = new ServerChatEventHandler();
    public ServerActorUpdateHandler     ServerActorUpdateHandler = new ServerActorUpdateHandler();
    public int                          ClientHostID => m_MyID;

    #region private
    [SerializeField] private int    m_MyID;
    private NetClient               m_netClient = null;
    private Stub                    m_ClientStub = null;
    private Proxy                   m_ClientProxy = null;

    #endregion

    void Update()
    {
        m_netClient.FrameMove();
    }

    private void OnDestroy()
    {
        m_netClient.Disconnect();
    }

    public void UpdateAnimation(int AnimState, float AnimTime)
    {

    }

    public void Send_Message(String text)
    {
        m_ClientProxy.OnChat(HostID.HostID_Server, RmiContext.ReliableSend, m_MyID, text);
    }

    public void Log_In(int Type, LOGIN_INFO LoginInfo)
    {
        m_ClientProxy.OnGameLogin(HostID.HostID_Server, RmiContext.ReliableSend, m_MyID, Type, 
                                  LoginInfo.user_id, LoginInfo.Password,
                                  LoginInfo.UID, LoginInfo.Email);
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

    public void Spawn_PlayerEvent(int iLeveLID)
    {
        m_ClientProxy.SpawnPlayerEvent(HostID.HostID_Server, RmiContext.ReliableSend, m_MyID, iLeveLID);
    }

    public void Spawn_Event(int iLeveLID, int iObjectID, int iSpawnPointID)
    {
        m_ClientProxy.SpawnObjectEvent(HostID.HostID_Server, RmiContext.ReliableSend, iLeveLID, iObjectID, iSpawnPointID);
    }

    #region Private
        private RESULT InitalizedClient()
        {
            m_netClient = new NetClient();
            // 파라미터 정의
            NetConnectionParam ClientParam = new NetConnectionParam();
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
            m_ClientStub.OnChat += ServerChatHandler.OnChat;
            m_ClientStub.ResponseLoginEvent += ServerLoginHandler.ResponseLoginEvent;
            m_ClientStub.OnPlayerJoined += ServerActorUpdateHandler.OnPlayerJoined;
            m_ClientStub.OnOtherPlayerUpdated += ServerActorUpdateHandler.OnOtherPlayerUpdated;

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
            {
                m_MyID = (int)m_netClient.GetLocalHostID();
                Debug.Log("Player Join");
            }
            else
                Debug.Log("Player Join Fail");
        }
        #endregion

    #region SingleTon
    static GameClient m_pInstance = null;
    public static GameClient Get_Instance() { return m_pInstance; }

    void Awake()
    {
        if (null == m_pInstance)
        {
            m_pInstance = this;
            m_pInstance.InitalizedClient();
            DontDestroyOnLoad(m_pInstance);
            Debug.Log("Create Game Client");
        }
        else
            Destroy(m_pInstance);
    }

    #endregion
}
