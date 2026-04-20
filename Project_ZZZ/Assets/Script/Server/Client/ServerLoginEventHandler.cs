using Nettention.Proud;
using System;
using UnityEngine;

public class ServerLoginEventHandler
{
    public event Action<bool, int> ResultEvent;
    public bool ResponseLoginEvent(HostID remote, RmiContext rmiContext, bool bIsSuccess, int LoginMsg)
    {
        ResultEvent.Invoke(bIsSuccess, LoginMsg);
        return true;
    }
}