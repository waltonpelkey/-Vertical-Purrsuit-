//  File:  "Floor.cpp"
//  Author: Walton Pelkey
//  Last Edit: 2/28/25
//  Description:  C++ file defining the Floor class for Vertical Purrsuit

// Engine includes
#include "EventCollision.h"

// Game includes
#include "Floor.h"

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

	// Set initial position to bottom of screen
	setPosition(df::Vector(WM.getBoundary().getHorizontal() / 2.0f, WM.getBoundary().getVertical() - (this->getBox().getVertical() / 2)));
}

// Destructor for floor class 
Floor::~Floor() {}

// Floor Event Handler 
// Return 0 if ignored, else 1.  
//int Floor::eventHandler(const df::Event* p_e) {
//
//}