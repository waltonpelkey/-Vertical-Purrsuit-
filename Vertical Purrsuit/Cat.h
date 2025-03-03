//  File:  "Cat.h"
//  Author: Walton Pelkey
//  Last Edit: 2/28/25
//  Description:  Header file defining the Cat class for Vertical Purrsuit

#ifndef __CAT_H__ 
#define __CAT_H__

// System includes
#include <string>

// Engine includes
#include "Object.h" 
#include "Event.h"
#include "EventStep.h"
#include "Vector.h"
#include "EventKeyboard.h" 
#include "EventCollision.h"

// Game includes
#include "Cat.h"

using namespace df;

// Class definition for cat
class Cat : public df::Object {

	// Const values for easy physics update
	const float GRAVITY = 0.03;
	const float X_FRICTION = 0.025;
	const float JUMP = 1.4;
	const float SIDEWAYS_MOVEMENT = 1;
	const float X_SPEED_MAX = 2;
	const float X_SPEED_MIN = -2;
	const float MAX_Y = 4;

private:
	bool isAlive;                          // Cat's alive status 
	bool isDoubleJump;                     // Used to disable double jump 
	bool isGrounded;					   // Cat vertical collision status
	bool platformCollision = false;        // Marks whether cat stood on a platform on each step
	bool floorCollision = false;           // Marks whether cat stood on a platform on each step
	bool groundedOnPlatform = false;
	Object* currentPlatform = nullptr;   

public:
	bool hasJumped = false;

	// Constructor for cat class 
	Cat();

	// Destructor for cat class 
	~Cat();

	// This function sets the initial position of the cat 
	int moveToStart();

	// This function determines the appropriate sprite for the cat 
	void assignSprite();

	// This function calculates the new velocity of the cat based on physics 
	df::Vector gravityUpdate();

	// Cat Event Handler 
	// Return 0 if ignored, else 1.  
	int eventHandler(const df::Event* p_e);

	// Run on each frame 
	void step(); 

	// Take appropriate action according to key pressed 
	void kbd(const df::EventKeyboard* p_keyboard_event); 

	// Wrap cat around to opposite side of world view
	void out();

	// Check for collision type and take appropriate action
	void collision(const df::EventCollision* p_e); 

	// If cat is grounded account for friction
	df::Vector frictionUpdate();
};

#endif // __CAT_H__ 