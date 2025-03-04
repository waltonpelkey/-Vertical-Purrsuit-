//  File: "Catnip.h"
//  Last Edit: 3/3/25
//  Description: Defines the Catnip class for Vertical Purrsuit

#ifndef __CATNIP_H__
#define __CATNIP_H__

// Engine includes
#include "Object.h"

// Game includes
#include "Platform.h"

// Catnip class
// Powerup item that the cat can collect
class Catnip : public df::Object {
private:
	Platform* p_platform;                  // Pointer to platform where catnip spawned

public:
	// Constructor that places catnip on given platform
	Catnip(Platform* platform);

	// Catnip Event Handler 
	// Return 0 if ignored, else 1. 
	int eventHandler(const df::Event* p_e) override;

	// Triggers the catnip effect and deletes itself
	void collect();

	// Moves the catnip with the platform
	void updatePosition();
};

#endif
