#pragma once

namespace ClientToServer {


	//Message ID that replies to each RMI method. 
               
    static const ::Proud::RmiID Rmi_OnPositionUpdated = (::Proud::RmiID)(2000+1);
               
    static const ::Proud::RmiID Rmi_OnChat = (::Proud::RmiID)(2000+2);

	// List that has RMI ID.
	extern ::Proud::RmiID g_RmiIDList[];
	// RmiID List Count
	extern int g_RmiIDListCount;

}


 

// Forward declarations


// Declarations



