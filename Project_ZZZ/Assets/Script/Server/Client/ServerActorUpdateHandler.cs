using Nettention.Proud;
using System;
using System.Collections.Generic;
using System.Resources;
using UnityEngine;

public class ServerActorUpdateHandler
{
    struct Player_Info
    {
        public Player              player;
        public Player_Controller   controller;
    }

    private Dictionary<int, Player_Info>        m_Players = new Dictionary<int, Player_Info>();
    private Dictionary<int, Character>          m_Monsters = new Dictionary<int, Character>();

    private void SpawnObjectEvent(HostID remote, RmiContext rmiContext, string Key, int templetedID, float px, float py, float pz)
    {
        if (!m_Monsters.ContainsKey(templetedID))
        {
            GameObject Prefab = CResourceManager.Get_Instance().Get_Prefab(Key);
            GameObject pNewPlayer = GameObject.Instantiate(Prefab);

      /*      Player_Info player;
            player.player = pNewPlayer.GetComponent<Player>();
            player.controller = pNewPlayer.GetComponent<Player_Controller>();

            m_Monsters.Add(TempeletedID, player);*/
        }
    }

    public bool OnPlayerJoined(HostID remote, RmiContext rmiContext, int clientId, string NickName, float px, float py, float pz)
    {
        int MyID = GameClient.Get_Instance().ClientHostID;
        if (!m_Players.ContainsKey(clientId))
        {
            GameObject Prefab = CResourceManager.Get_Instance().Get_Prefab("Player");
            GameObject pNewPlayer = GameObject.Instantiate(Prefab);

            if (clientId == MyID)
                 pNewPlayer.name = "Player";
             else
                 pNewPlayer.name = "other" + clientId;

            Player_Info player;
            player.player = pNewPlayer.GetComponent<Player>();
            player.controller = pNewPlayer.GetComponent<Player_Controller>();

            m_Players.Add(clientId, player);
        }
        return true;
    }

    public bool OnOtherPlayerUpdated(HostID remote, RmiContext rmiContext, int clientId, string NickName, 
                                    float ScaleX, float ScaleY, float ScaleZ,
                                    float RotX, float RotY, float RotZ, float RotW,
                                    float px, float py, float pz)
    {
        if (m_Players.ContainsKey(clientId))
        {
            m_Players[clientId].controller.Update_Transform(new Vector3(ScaleX, ScaleY, ScaleZ),
                                                            new Quaternion(RotX, RotY, RotZ, RotW),
                                                            new Vector3(px, py, pz));
        }
        else
            OnPlayerJoined(remote, rmiContext, clientId, NickName, px, py, pz);

        return true;
    }

    public bool OnOtherActorUpdated(HostID remote, RmiContext rmiContext, int templetedID, string NickName,
                                    float ScaleX, float ScaleY, float ScaleZ,
                                    float RotX, float RotY, float RotZ, float RotW,
                                    float px, float py, float pz)
    {
        if (m_Players.ContainsKey(templetedID))
        {
            m_Players[templetedID].controller.Update_Transform( new Vector3(ScaleX, ScaleY, ScaleZ),
                                                                new Quaternion(RotX, RotY, RotZ, RotW),
                                                                new Vector3(px, py, pz));
        }

        return true;
    }
}