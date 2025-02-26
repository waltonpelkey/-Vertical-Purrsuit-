//
// EventNetworkConnect.h
//
// Generated when a new socket connection has been connected.
//

#ifndef NO_NETWORK

#ifndef __EVENT_NETWORK_CONNECT_H__
#define __EVENT_NETWORK_CONNECT_H__

// Engine includes.
#include "EventNetwork.h"

namespace df {

const std::string NETWORK_CONNECT_EVENT = "df-network-connect";

class EventNetworkConnect : public EventNetwork {

 public:
  // Constructor must provide label.
  EventNetworkConnect(NetworkEventLabel label);
};

} // end of namespace df

#endif // __EVENT_NETWORK_CONNECT_H__

#endif // NO_NETWORK
