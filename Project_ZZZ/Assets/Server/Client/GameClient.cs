using ClientToServer;
using ServerToClient;

using InputCommand;
using Nettention.Proud;
using UnityEditor.PackageManager;
using UnityEngine;

public class GameClient : MonoBehaviour
{
    NetClient       m_netClient = null;
    Stub            m_ClientStub = null;
    Proxy           m_ClientProxy = null;

    void Start()
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

            m_ClientProxy.OnPositionUpdated(HostID.HostID_Server, RmiContext.UnreliableSend, (int)m_netClient.GetLocalHostID(),
                   CurPos.x, CurPos.y, CurPos.z, NewDir.x, NewDir.y, NewDir.z);
        }
    }

    private bool OnPositionUpdated(HostID remote, RmiContext rmiContext, int clientId, float px, float py, float pz, float dx, float dy, float dz)
    {
        gameObject.transform.position = new Vector3(px, py, pz);
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
