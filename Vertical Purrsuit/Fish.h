//  File:  "Fish.h"
//  Last Edit: 3/3/25
//  Description: Defines the Fish class for Vertical Purrsuit

#ifndef __FISH_H__
#define __FISH_H__

// Engine includes
#include "Object.h"
#include "Event.h"

// Game includes
#include "Platform.h"

// Fish class
// Collectable item that increases the players points
class Fish : public df::Object {
private:
	const int POINTS = 100;    // Point total awarded for collecting
	Platform* p_platform;      // Platform associated with the fish

public:
	// Constructor
	Fish(Platform* platform);

	// Fish Event Handler 
	// Return 0 if ignored, else 1. 
	int eventHandler(const df::Event* p_e) override;

	// Collects the fish and adds points to the score
	void collect();

	// Updates the fish's position to stay on the platform
	void updatePosition();
};

#endif

