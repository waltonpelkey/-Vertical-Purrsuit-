//  File: "Platform.cpp"
//  Last Edit: 3/3/25
//  Description: Defines the Platform class for Vertical Purrsuit

// Engine includes
#include "DisplayManager.h"
#include "EventOut.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "Object.h"

// Game includes
#include "Platform.h"
#include "Fish.h"

// Constructor
Platform::Platform(float y_pos) {
	// Assign random difficulty value
	m_diff = rand() % 100;

	// Set sprite and type
	setSprite("base-platform");
	setType("baseplatform");

	// Set to soft to allow for collision event 
	// but no impeded movement
	setSolidness(df::SOFT); 
	
	// Move platform to starting position
	moveToStart(y_pos);

	// Assign a random horizontal velocity
	m_velocity = ((rand() % 10) + 3);
	v = m_velocity / 10.0f;

	// Set platform movement
	setVelocity(df::Vector(v, 0));

	// Make sure cat is drawn over top
	setAltitude(0);

	// Register interest for step events
	registerInterest(df::STEP_EVENT); 

	// Log creation
	LM.writeLog("platform created with velocity %d and difficulty %d\n", m_velocity, m_diff);

}

// Move platform to a new random x position given a y level
void Platform::moveToStart(float y_pos) {
	df::Vector temp_pos;
	float horiz = WM.getBoundary().getHorizontal();

	// Set random x position
	temp_pos.setX((rand() % (int)(horiz - 10)) + 5); 
	temp_pos.setY(y_pos);  

	// Ensure platform is not colliding with other objects
	df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
	while (collision_list.getCount() != 0) {
		temp_pos.setX(temp_pos.getX() + 5);  // Move slightly to the right to prevent overlapping
		collision_list = WM.getCollisions(this, temp_pos);
	}

	// Move platform to the final position
	WM.moveObject(this, temp_pos);
}

// Handles events
int Platform::eventHandler(const df::Event* p_e) {
	// Check for out event
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}

	// Check for step event
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	// Check for collision event
	if (p_e->getType() == df::COLLISION_EVENT) {

	}
	return 0;
}

// Handles out of bounds logic
void Platform::out() {
	// If platform moves above the view ignore out of bounds event
	if (getPosition().getY() <= WM.getView().getCorner().getY()){
		return;
	}

	// If the platofmr moves below the view then delete it
	// Added a small buffer for player sanity
	if (getPosition().getY() >= (WM.getView().getCorner().getY() + DM.getVertical() + 5)) {
		WM.markForDelete(this);
		return;
	}

	// If platform goes off screen horizontal then reverse x direction
	if (getPosition().getX() >= WM.getView().getCorner().getX() + WM.getView().getHorizontal() || getPosition().getX() <= WM.getView().getCorner().getX()) {
		v = v * -1;
		setVelocity(df::Vector(v, 0));
		LM.writeLog("Velocity is now %d\n", v);
	}
}

// Handle movement on each step
void Platform::step() {
	// Get platform edges
	float platform_left = getPosition().getX() - (this->getBox().getHorizontal() / 2.0f);
	float platform_right = getPosition().getX() + (this->getBox().getHorizontal() / 2.0f);

	// Get current view boundaries
	float view_left = WM.getView().getCorner().getX();
	float view_right = view_left + WM.getView().getHorizontal();

	// Reverse velocity when edges reach the view boundary
	if (platform_left <= view_left) {
		setPosition(df::Vector(view_left + (this->getBox().getHorizontal() / 2.0f), getPosition().getY()));
		setVelocity(df::Vector(abs(v), 0));  // Move right
	}
	else if (platform_right >= view_right) {
		setPosition(df::Vector(view_right - (this->getBox().getHorizontal() / 2.0f), getPosition().getY()));
		setVelocity(df::Vector(-abs(v), 0));  // Move left
	}

	// Check if below the view and mark for deletion
	float view_bottom = WM.getView().getCorner().getY() + WM.getView().getVertical(); 
	if (getPosition().getY() > view_bottom) {
		LM.writeLog("Platform at (%f, %f) has exited the view and will be deleted.",
			getPosition().getX(), getPosition().getY());

		// Remove the platform from the world
		WM.markForDelete(this);
		return;
	}
}