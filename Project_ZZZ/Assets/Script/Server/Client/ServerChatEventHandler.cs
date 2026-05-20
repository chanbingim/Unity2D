using Nettention.Proud;
using System;
using UnityEngine;

public class ServerChatEventHandler
{
    public event Action<String> ChatEvent;
    public bool OnChat(HostID remote, RmiContext rmiContext, int ClienID, string Message)
    {
        ChatEvent.Invoke(Message);
        return true;
    }

}