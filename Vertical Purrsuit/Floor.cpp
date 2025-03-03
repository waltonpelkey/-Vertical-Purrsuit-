//  File:  "Floor.cpp"
//  Author: Walton Pelkey
//  Last Edit: 2/28/25
//  Description:  C++ file defining the Floor class for Vertical Purrsuit

// Engine includes
#include "EventCollision.h"

// Game includes
#include "Floor.h"
#include "Object.h"
#include <EventStep.h>
#include <GameManager.h>
#include "Cat.h"

// Constructor for floor class 
Floor::Floor() {
	// Set sprite to cat sprite
	setSprite("floor");

	// Set object type to Cat
	setType("Floor");

	// Set initial velocity to (0,0)
	setVelocity(df::Vector(0, 0));

	// Need to update the physics
	registerInterest(df::COLLISION_EVENT);

	registerInterest(df::STEP_EVENT);

	// Get initial view boundary
	df::Vector temp_pos;

	// Get world boundaries
	float view_horiz = WM.getBoundary().getHorizontal();
	float view_vert = WM.getBoundary().getVertical();

	// X is centered on window
	temp_pos.setX((view_horiz / 2.0f));

	// Y is at bottom of window
	temp_pos.setY(view_vert);

	WM.moveObject(this, temp_pos);
}

// Destructor for floor class 
Floor::~Floor() {}

// Floor Event Handler 
// Return 0 if ignored, else 1.  
int Floor::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast<const df::EventCollision*>(p_e);
		if (p_collision_event) {
			collision(p_collision_event);
		}
		return 1;
	}
	return 0;
}

// Handles collisions
void Floor::collision(const df::EventCollision* p_e) {
	Cat* cat = dynamic_cast<Cat*>(p_e->getObject1()->getType() == "Cat" ? p_e->getObject1() :
		(p_e->getObject2()->getType() == "Cat" ? p_e->getObject2() : nullptr));

	// If the cat has jumped and touches the floor, trigger Game Over
	if (cat && cat->hasJumped) {
		GM.setGameOver();
	}
}