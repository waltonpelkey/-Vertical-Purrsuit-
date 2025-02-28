//  File:  "Cat.cpp"
//  Author: Walton Pelkey
//  Last Edit: 2/27/25
//  Description:  C++ file defining the Cat class for Vertical Purrsuit

// System includes
#include <string>

// Engine includes
#include "LogManager.h"
#include "Object.h" 
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Vector.h"
#include "Event.h"
#include "EventStep.h"

// Game includes
#include "Cat.h"

// Constructor for cat class
Cat::Cat() {
	// Set sprite to cat sprite
	setSprite("cat-dropping-left");

	// Set object type to Cat
	setType("Cat");

	// Set initial velocity to (0,0)
	setVelocity(df::Vector(0, 0));

	// Need to update the physics
	registerInterest(df::STEP_EVENT);

	// Need for the cat to jump
	registerInterest(df::KEYBOARD_EVENT);

	// Set alive to true
	isAlive = true;

	// Set double jump to false
	isDoubleJump = false;
}

// Destructor for cat class
Cat::~Cat() {}

/*
 * This function sets the initial position of the cat
 *
 * @param
 * @return 0 if okay, else -1
 */
int Cat::moveToStart() {
	df::Vector temp_pos;

	// Get world boundaries
	float world_horiz = (int)WM.getBoundary().getHorizontal();
	float world_vert = (int)WM.getBoundary().getVertical();

	// X is centered on window
	temp_pos.setX(world_horiz / 2.0f);

	// Y is at bottom of window
	temp_pos.setY(world_vert / 2.0f);

	WM.moveObject(this, temp_pos);

	// If successful 
	return 0;
}

// This function determines the appropriate sprite for the cat
std::string Cat::assignSprite() {
	// Get cat y velocity
	float y_veloc = this->getVelocity().getY();
	// Get cat x velocity
	float x_veloc = this->getVelocity().getX();

	// If y velocity is more than 0
	if (y_veloc > 0) {
		// If x direction more than 0
		if (x_veloc > 0) {
			std::string sprite = "cat-dropping-right";
			return sprite;
		}
		// If x direction less than or equal to 0
		else {
			std::string sprite = "cat-dropping-left";
			return sprite;
		}
	}

	// If y velocity is less than 0
	else if (y_veloc < 0) {
		// If x direction more than 0
		if (x_veloc > 0) {
			std::string sprite = "cat-rising-right";
			return sprite;
		}
		// If x direction less than or equal to 0
		else {
			std::string sprite = "cat-rising-left";
			return sprite;
		}
	}


	// If x velocity is more than 0
	else if (x_veloc > 0) {
		std::string sprite = "cat-walking-right";
		return sprite; 
	}

	// If x velocity is less than 0
	else if (x_veloc < 0) {
		std::string sprite = "cat-walking-left";
		return sprite; 
	}

	// Else return "cat-idle"
	// Currently set to cat dropping right as a test
	else {
		std::string sprite = "cat-dropping-right";
		return sprite; 
	}
}

// This function calculates the new velocity of the cat based on physics
df::Vector Cat::gravityUpdate() {
	float y_veloc = this->getVelocity().getY();
	float x_veloc = this->getVelocity().getX();
	y_veloc = y_veloc + GRAVITY;
	df::Vector new_vector = df::Vector(x_veloc, y_veloc);

	return new_vector;
}

// Cat Event Handler
// Return 0 if ignored, else 1.
int Cat::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event = dynamic_cast <const df::EventKeyboard*> (p_e);
		if (p_keyboard_event) {
			kbd(p_keyboard_event);
		}
		return 1;
	}
	if (p_e->getType() == df::STEP_EVENT) {
		const df::EventStep* p_step_event = dynamic_cast<const df::EventStep*>(p_e);
		// On the first step, move to start position
		if (p_step_event && p_step_event->getStepCount() == 0) {
			moveToStart();
		}
		step(p_step_event); 
		return 1;
	}
	return 0;
}

// Run on each frame
void Cat::step(const df::EventStep* p_step_event) {
	df::Vector vector = gravityUpdate();
	this->setVelocity(vector);
	std::string new_sprite = assignSprite();
	this->setSprite(new_sprite);

	if (this->getPosition().getY() >= (WM.getView().getVertical() - (getBox().getVertical() / 2.0f)) ) {  
		WM.moveObject(this, df::Vector(getPosition().getX(), (WM.getView().getVertical() - (getBox().getVertical() / 2.0f)))); 
	}
	else {
		// Allows cat to get off the ground
		if (p_step_event && p_step_event->getStepCount() % 4 == 0) {
			WM.moveObject(this, vector + this->getPosition()); 
		}
	}
	
}

// Take appropriate action according to key pressed
void Cat::kbd(const df::EventKeyboard* p_keyboard_event) {
	if (!p_keyboard_event) return;

	switch (p_keyboard_event->getKey()) {
	case df::Keyboard::SPACE: // Jump
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			this->setVelocity(df::Vector(this->getVelocity().getX(), this->getVelocity().getY() - JUMP));
		}
		break;
	default: // key event doesnt do anything
		return;
	};

	return;
}