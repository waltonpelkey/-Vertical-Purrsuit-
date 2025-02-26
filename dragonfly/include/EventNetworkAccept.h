//
// EventNetworkAccept.h
//
// Generated when a new socket connection has been accepted.
//

#ifndef NO_NETWORK

#ifndef __EVENT_NETWORK_ACCEPT_H__
#define __EVENT_NETWORK_ACCEPT_H__

// Engine includes.
#include "EventNetwork.h"

namespace df {

const std::string NETWORK_ACCEPT_EVENT = "df-network-accept";

class EventNetworkAccept : public EventNetwork {

 public:
  // Constructor must provide label.
  EventNetworkAccept(NetworkEventLabel label);
};

} // end of namespace df

#endif // __EVENT_NETWORK_ACCEPT_H__

#endif // NO_NETWORK
