//  File:  "Floor.cpp"
//  Last Edit: 3/3/25
//  Description: Defines the Floor class for Vertical Purrsuit

// Engine includes
#include "EventCollision.h"
#include "Object.h"
#include "EventStep.h"
#include "GameManager.h"

// Game includes
#include "Floor.h"
#include "Cat.h"

// Constructor
Floor::Floor() {
	// Set sprite to cat sprite
	setSprite("floor");

	// Set object type to Cat
	setType("Floor");

	// Set initial velocity to (0,0)
	setVelocity(df::Vector(0, 0));

	// Register interest in events
	registerInterest(df::COLLISION_EVENT);
	registerInterest(df::STEP_EVENT);

	// Get initial view boundary
	df::Vector temp_pos;
	float view_horiz = WM.getBoundary().getHorizontal();
	float view_vert = WM.getBoundary().getVertical();
	temp_pos.setX((view_horiz / 2.0f));                  // X is centered on window
	temp_pos.setY(view_vert);							 // Y is at bottom of window
	WM.moveObject(this, temp_pos);
}

// Floor Event Handler 
// Return 0 if ignored, else 1.  
int Floor::eventHandler(const df::Event* p_e) {
	// Check for collision event
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast<const df::EventCollision*>(p_e);
		if (p_collision_event) {
			// Hand collision
			collision(p_collision_event);
		}
		return 1;
	}
	return 0;
}

// Handles collisions
void Floor::collision(const df::EventCollision* p_e) {
	// Get the cat object from the collision
	Cat* cat = dynamic_cast<Cat*>(p_e->getObject1()->getType() == "Cat" ? p_e->getObject1() :
		(p_e->getObject2()->getType() == "Cat" ? p_e->getObject2() : nullptr));

	// If it was cat that collided and
	// If the cat has jumped and touches the floor, trigger Game Over
	if (cat && cat->hasJumped) {
		GM.setGameOver();
	}
}