#pragma once

namespace ServerToClient {


	//Message ID that replies to each RMI method. 
               
    static const ::Proud::RmiID Rmi_OnPlayerJoined = (::Proud::RmiID)(3000+1);
               
    static const ::Proud::RmiID Rmi_OnOtherPlayerUpdated = (::Proud::RmiID)(3000+2);
               
    static const ::Proud::RmiID Rmi_OnPositionUpdated = (::Proud::RmiID)(3000+3);
               
    static const ::Proud::RmiID Rmi_UpdateCharacterAnimState = (::Proud::RmiID)(3000+4);
               
    static const ::Proud::RmiID Rmi_ResponseCheckNickname = (::Proud::RmiID)(3000+5);
               
    static const ::Proud::RmiID Rmi_OnChat = (::Proud::RmiID)(3000+6);

	// List that has RMI ID.
	extern ::Proud::RmiID g_RmiIDList[];
	// RmiID List Count
	extern int g_RmiIDListCount;

}


 

// Forward declarations


// Declarations



