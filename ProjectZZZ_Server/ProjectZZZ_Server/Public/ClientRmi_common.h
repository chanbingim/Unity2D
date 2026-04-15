#pragma once

namespace ClientToServer {


	//Message ID that replies to each RMI method. 
               
    static const ::Proud::RmiID Rmi_OnGameLogin = (::Proud::RmiID)(2000+1);
               
    static const ::Proud::RmiID Rmi_Create_Character = (::Proud::RmiID)(2000+2);
               
    static const ::Proud::RmiID Rmi_RequestCheckNickname = (::Proud::RmiID)(2000+3);
               
    static const ::Proud::RmiID Rmi_OnPositionUpdated = (::Proud::RmiID)(2000+4);
               
    static const ::Proud::RmiID Rmi_OnAnimUpdated = (::Proud::RmiID)(2000+5);
               
    static const ::Proud::RmiID Rmi_OnChat = (::Proud::RmiID)(2000+6);

	// List that has RMI ID.
	extern ::Proud::RmiID g_RmiIDList[];
	// RmiID List Count
	extern int g_RmiIDListCount;

}


 

// Forward declarations


// Declarations



