#pragma once

namespace ClientToServer {


	//Message ID that replies to each RMI method. 
               
    static const ::Proud::RmiID Rmi_OnGameLogin = (::Proud::RmiID)(2000+1);
               
    static const ::Proud::RmiID Rmi_Create_Character = (::Proud::RmiID)(2000+2);
               
    static const ::Proud::RmiID Rmi_SpawnObjectEvent = (::Proud::RmiID)(2000+3);
               
    static const ::Proud::RmiID Rmi_SpawnPlayerEvent = (::Proud::RmiID)(2000+4);
               
    static const ::Proud::RmiID Rmi_RequestCheckNickname = (::Proud::RmiID)(2000+5);
               
    static const ::Proud::RmiID Rmi_OnPositionUpdated = (::Proud::RmiID)(2000+6);
               
    static const ::Proud::RmiID Rmi_OnActorPositionUpdated = (::Proud::RmiID)(2000+7);
               
    static const ::Proud::RmiID Rmi_OnAnimUpdated = (::Proud::RmiID)(2000+8);
               
    static const ::Proud::RmiID Rmi_OnActorAnimUpdated = (::Proud::RmiID)(2000+9);
               
    static const ::Proud::RmiID Rmi_Request_AddItem = (::Proud::RmiID)(2000+10);
               
    static const ::Proud::RmiID Rmi_Request_RemoveItem = (::Proud::RmiID)(2000+11);
               
    static const ::Proud::RmiID Rmi_Request_ItemData = (::Proud::RmiID)(2000+12);
               
    static const ::Proud::RmiID Rmi_Request_AddGold = (::Proud::RmiID)(2000+13);
               
    static const ::Proud::RmiID Rmi_OnChat = (::Proud::RmiID)(2000+14);

	// List that has RMI ID.
	extern ::Proud::RmiID g_RmiIDList[];
	// RmiID List Count
	extern int g_RmiIDListCount;

}


 

// Forward declarations


// Declarations



