#include "Platform.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "EventOut.h"
#include "EventStep.h"
#include "LogManager.h"
#include "Fish.h"
#include "Object.h"

Platform::Platform(float y_pos) {
	m_diff = rand() % 100;
	setSprite("base-platform");
	setSolidness(df::SOFT);
	setType("baseplatform");
	moveToStart(y_pos);
	m_velocity = ((rand() % 10) + 3);
	v = m_velocity / 10.0f;
	LM.writeLog("platform created with velocity %d and difficulty %d\n", m_velocity, m_diff);
	setVelocity(df::Vector(v, 0));
	setAltitude(0);
	registerInterest(df::STEP_EVENT); 
}

void Platform::moveToStart(float y_pos) {
	df::Vector temp_pos;

	float horiz = WM.getBoundary().getHorizontal();

	temp_pos.setX((rand() % (int)(horiz - 10)) + 5); 
	temp_pos.setY(y_pos);  

	// Ensure platform is not colliding with other objects
	df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
	while (collision_list.getCount() != 0) {
		temp_pos.setX(temp_pos.getX() + 5);  // Move slightly to the right to prevent overlapping
		collision_list = WM.getCollisions(this, temp_pos);
	}

	WM.moveObject(this, temp_pos);
}


int Platform::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {

	}
	

}

void Platform::out() {
	if (getPosition().getY() <= WM.getView().getCorner().getY()){
		return;
	}
	if (getPosition().getY() >= (WM.getView().getCorner().getY() + DM.getVertical() + 3)) {
		WM.markForDelete(this);
		return;
	}
	if (getPosition().getX() >= WM.getView().getCorner().getX() + WM.getView().getHorizontal() || getPosition().getX() <= WM.getView().getCorner().getX()) {
		v = v * -1;
		setVelocity(df::Vector(v, 0));
		LM.writeLog("Velocity is now %d\n", v);
	}
}

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

Platform::~Platform() {}