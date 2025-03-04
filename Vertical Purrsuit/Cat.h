//  File: "Cat.h"
//  Last Edit: 3/3/25
//  Description: Defines the Cat class for Vertical Purrsuit

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

// The main player character class
class Cat : public df::Object {

	// Physics constants
	const float GRAVITY = 0.03;            // Acceleration due to gravity
	const float X_FRICTION = 0.025;		   // Friction applied horizontally
	const float JUMP = 1.4;                // Jump strength
	const float SIDEWAYS_MOVEMENT = 1;     // Cat's horizontal movement aceleration per step
	const float X_SPEED_RIGHT = 2;         // Max horizontal speed to the right
	const float X_SPEED_LEFT = -2;         // Max horizontal speed to the left
	const float MAX_Y = 4;                 // Max falling speed (terminal velocity)

private:
	// State variables
	bool isAlive;                          // Cat's alive status 
	bool isGrounded;					   // Marks whether the cat is on a hard surface
	bool platformCollision = false;        // Marks whether cat stood on a platform on each step
	bool floorCollision = false;           // Marks whether cat stood on the floor on each step
	bool groundedOnPlatform = false;       // If the cat is on a platform
	Object* currentPlatform = nullptr;     // The platform the cat is currently on
	Object* lastPlatform = nullptr;        // The last platform the cat stood on

	// Catnip variables
	int catnip_timer;                      // Timer for catnip
	bool isCatnipActive;                   // If catnip effect is active

public:
	bool hasJumped = false;                // Whether the cat has jumped since the beginning of the game (placeholder for game over)

	// Constructor
	Cat();

	// Destructor (place holder)
	~Cat();

	// Moves cat to starting position
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