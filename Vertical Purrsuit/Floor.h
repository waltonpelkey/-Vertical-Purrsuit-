//  File:  "Floor.h"
//  Author: Walton Pelkey
//  Last Edit: 2/28/25
//  Description:  Header file defining the Floor class for Vertical Purrsuit

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
	// Constructor for floor class 
	Floor(); 

	// Destructor for floor class 
	~Floor(); 

	// Floor Event Handler 
	// Return 0 if ignored, else 1.  
	int eventHandler(const df::Event* p_e) override;

	// Collisions
	void collision(const df::EventCollision* p_e);
};

#endif // __FLOOR_H__ 