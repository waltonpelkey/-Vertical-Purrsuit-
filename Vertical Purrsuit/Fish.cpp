//  File:  "Fish.cpp"
//  Last Edit: 3/3/25
//  Description: Defines the Fish class for Vertical Purrsuit

// Engine includes
#include "EventCollision.h"
#include "LogManager.h"
#include "WorldManager.h"

// Game includes
#include "Fish.h"
#include "Score.h"
#include "EventScore.h"
#include "Platform.h"

Fish::Fish(Platform* platform) {
	setType("Fish");                           // Set type
	setSprite("fish");                         // Set sprite

	// Register for events
	registerInterest(df::COLLISION_EVENT);  
	registerInterest(df::STEP_EVENT);

	// Position fish slightly above its platform
	p_platform = platform;
	df::Vector platform_pos = platform->getPosition();
	setPosition(df::Vector(platform_pos.getX(), platform_pos.getY() - (platform->getBox().getVertical() / 2.0f) - 0.03)); 
	
	// Log spawn
	LM.writeLog("Fish spawned at (%f, %f)", platform_pos.getX(), platform_pos.getY() - (platform->getBox().getVertical() / 2.0f) - 0.03); 
}

// Handles events
int Fish::eventHandler(const df::Event* p_e) {
	// Check for collision
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast<const df::EventCollision*>(p_e);
		if (p_collision_event) {
			// Determine which object is not this
			df::Object* p_other = (p_collision_event->getObject1() == this) ?
				p_collision_event->getObject2() :
				p_collision_event->getObject1();

			// Check if other object is the Cat 
			// if so then call collect
			if (p_other->getType() == "Cat") {
				collect();
				return 1;
			}
		}
	}
	
	// Check for step event
	if (p_e->getType() == df::STEP_EVENT) { 
		// Update position each step
		updatePosition(); 
		return 1;
	} 
	return 0;
}

// Handles collecting the fish
void Fish::collect() {
	// Trigger score event to add points
	EventScore score_event(POINTS);
	WM.onEvent(&score_event);

	// Log score update
	LM.writeLog("Fish collected. +%d points", POINTS); 

	// Remove the fish from the world after collection
	WM.markForDelete(this);
}

// Updates the fish's position to be same as platform
void Fish::updatePosition() {
	// Avoid crashes
	if (!p_platform) {
		WM.markForDelete(this);
	}

	// Keep fish slightly above platform
	df::Vector platform_pos = p_platform->getPosition(); 
	setPosition(df::Vector(platform_pos.getX(), platform_pos.getY() - (p_platform->getBox().getVertical() / 2.0f) - 0.03)); 
}