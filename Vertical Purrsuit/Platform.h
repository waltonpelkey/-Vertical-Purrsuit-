//  File: "Platform.h"
//  Last Edit: 3/3/25
//  Description: Defines the Platform class for Vertical Purrsuit

// Engine includes
#include "Vector.h"
#include "Object.h"
#include "EventCollision.h"

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

// Platform class
// Moving platforms for the cat to land on
class Platform : public df::Object {
private:
	float m_velocity;   // Randomly assigned velocity value
	float v;            // Horizontal velocity
	int m_diff;         // Random difficulty factor

	// Moves platform to start position given a y_pos
	void moveToStart(float y_pos);

	// Handles out event
	void out();

	// Handles step event
	void step();

public:
	// Constructor
	Platform(float y_pos);

	// Handles events
	int eventHandler(const df::Event* p_e) override;
};

#endif