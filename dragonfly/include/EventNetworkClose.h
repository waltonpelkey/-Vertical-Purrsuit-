//
// EventNetworkClose.h
//
// Generated when a new socket connection has been closed.
//

#ifndef NO_NETWORK

#ifndef __EVENT_NETWORK_CLOSE_H__
#define __EVENT_NETWORK_CLOSE_H__

// Engine includes.
#include "EventNetwork.h"

namespace df {

const std::string NETWORK_CLOSE_EVENT = "df-network-close";

class EventNetworkClose : public EventNetwork {

 public:
  // Constructor must provide label.
  EventNetworkClose(NetworkEventLabel label);
};

} // end of namespace df

#endif // __EVENT_NETWORK_CLOSE_H__

#endif // NO_NETWORK
