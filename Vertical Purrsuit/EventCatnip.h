//  File: "CatnipEvent.h"
//  Last Edit: 3/3/25
//  Description: Defines the CatnipEvent class for Vertical Purrsuit

#ifndef __EVENT_CATNIP_H__
#define __EVENT_CATNIP_H__

// Engine includes
#include "Event.h"

// Event label
#define CATNIP_EVENT "Catnip"

// Event to alert registered objects about catnip collection
class EventCatnip : public df::Event {
public:
    // Constructor
    EventCatnip();
};

#endif

