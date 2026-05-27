#pragma once

namespace ServerToClient {


	//Message ID that replies to each RMI method. 
               
    static const ::Proud::RmiID Rmi_ResponseLoginEvent = (::Proud::RmiID)(3000+1);
               
    static const ::Proud::RmiID Rmi_ResponseCheckNickname = (::Proud::RmiID)(3000+2);
               
    static const ::Proud::RmiID Rmi_OnPlayerJoined = (::Proud::RmiID)(3000+3);
               
    static const ::Proud::RmiID Rmi_SpawnObjectEvent = (::Proud::RmiID)(3000+4);
               
    static const ::Proud::RmiID Rmi_OtherPlayerTransformUpdated = (::Proud::RmiID)(3000+5);
               
    static const ::Proud::RmiID Rmi_OnPlayerTransformUpdated = (::Proud::RmiID)(3000+6);
               
    static const ::Proud::RmiID Rmi_OtherActorTransformUpdated = (::Proud::RmiID)(3000+7);
               
    static const ::Proud::RmiID Rmi_ActorTransformUpdated = (::Proud::RmiID)(3000+8);
               
    static const ::Proud::RmiID Rmi_UpdateCharacterAnimState = (::Proud::RmiID)(3000+9);
               
    static const ::Proud::RmiID Rmi_OnOtherPlayerAnimUpdated = (::Proud::RmiID)(3000+10);
               
    static const ::Proud::RmiID Rmi_UpdateActorAnimState = (::Proud::RmiID)(3000+11);
               
    static const ::Proud::RmiID Rmi_OnOtherActorAnimUpdated = (::Proud::RmiID)(3000+12);
               
    static const ::Proud::RmiID Rmi_Response_UpdateSlot = (::Proud::RmiID)(3000+13);
               
    static const ::Proud::RmiID Rmi_Response_Gold = (::Proud::RmiID)(3000+14);
               
    static const ::Proud::RmiID Rmi_OnChat = (::Proud::RmiID)(3000+15);

	// List that has RMI ID.
	extern ::Proud::RmiID g_RmiIDList[];
	// RmiID List Count
	extern int g_RmiIDListCount;

}


 

// Forward declarations


// Declarations



