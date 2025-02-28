//
// Cat.h
//

#pragma once

// System includes
#include <string>

// Engine includes
#include "Object.h" 
#include "Event.h"
#include "EventStep.h"
#include "Vector.h"
#include "EventKeyboard.h"

// Game includes
#include "Cat.h"

using namespace df;

// Class definition for cat
class Cat : public df::Object {

	const float GRAVITY = 0.001;
	const float JUMP = 0.1;

private:
	bool isAlive;                  // Cat's alive status 
	bool isDoubleJump;               // Used to disable double jump 

public:
	// Constructor for cat class 
	Cat();

	// Destructor for cat class 
	~Cat();

	// This function sets the initial position of the cat 
	int moveToStart();

	// This function determines the appropriate sprite for the cat 
	std::string assignSprite();

	// This function calculates the new velocity of the cat based on physics 
	df::Vector gravityUpdate();

	// Cat Event Handler 
	// Return 0 if ignored, else 1.  
	int eventHandler(const df::Event* p_e);

	// Run on each frame 
	void step(const df::EventStep* p_step_event); 

	// Take appropriate action according to key pressed 
	void kbd(const df::EventKeyboard* p_keyboard_event); 

};