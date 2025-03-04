//  File:  "Catnip.cpp"
//  Last Edit: 2/28/25
//  Description: Defines the Catnip class for Vertical Purrsuit

// Engine includes
#include "EventCollision.h"
#include "EventStep.h"
#include "EventCatnip.h"
#include "WorldManager.h"
#include "LogManager.h"

// Game includes
#include "Catnip.h"

// Constructor
Catnip::Catnip(Platform* platform) {
	setType("Catnip");         // Set object type
	setSprite("catnip");       // Default sprite

    // Set position to match platform
    p_platform = platform;
    df::Vector platform_pos = platform->getPosition();
    setPosition(df::Vector(platform_pos.getX(), platform_pos.getY() - 2.0f));

    // Register interest for events
	registerInterest(df::COLLISION_EVENT);
	registerInterest(df::STEP_EVENT);
	
}

// Catnip Event Handler 
// Return 0 if ignored, else 1. 
int Catnip::eventHandler(const df::Event* p_e) {
    // Check for collision event
    if (p_e->getType() == df::COLLISION_EVENT) {
        const df::EventCollision* p_collision_event = dynamic_cast<const df::EventCollision*>(p_e);
        if (p_collision_event) {
            // Identify which object was not this
            df::Object* p_other = (p_collision_event->getObject1() == this) ?
                p_collision_event->getObject2() : p_collision_event->getObject1();
            
            // If collided with cat then call collect
            if (p_other->getType() == "Cat") {
                collect();
                return 1;
            }
        }
    }

    // Check for step event
    if (p_e->getType() == df::STEP_EVENT) { 
        const df::EventStep* p_step_event = dynamic_cast<const df::EventStep*>(p_e); 
        if (p_step_event) {
            // Update position every step
            updatePosition();
            return 1;
        }
    }
    return 0;
}

// When cat collects catnip, trigger power-up
void Catnip::collect() {
    // Send catnip effect event
    EventCatnip catnip_event;
    WM.onEvent(&catnip_event);
    LM.writeLog("Catnip collected! Activating 'high' mode!");

    // Remove the catnip from world after collecting
    WM.markForDelete(this);
}

//If the platform moved then move catnip with it
void Catnip::updatePosition() {
    // Prevent crashes if the platform is null
    if (!p_platform) {
        WM.markForDelete(this);
    }

    // Keep catnip slightly above the platform
    setPosition(df::Vector(p_platform->getPosition().getX(), p_platform->getPosition().getY() - 2.0f));
}
