//  File: "Floor.h"
//  Last Edit: 3/3/25
//  Description: Defines the Floor class for Vertical Purrsuit

#ifndef __FLOOR_H__ 
#define __FLOOR_H__

// System includes
#include <string>

// Engine includes
#include "Object.h" 
#include <WorldManager.h>

using namespace df;

// Class definition for cat
class Floor : public df::Object {
public:
	// Constructor
	// Sets floor to bottom of world and bottom of the initial view
	Floor(); 

	// Floor Event Handler 
	// Return 0 if ignored, else 1.  
	int eventHandler(const df::Event* p_e) override;

	// Handles collisions logic with the cat
	void collision(const df::EventCollision* p_e);
};

#endif // __FLOOR_H__ 