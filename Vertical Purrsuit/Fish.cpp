//  File:  "Fish.cpp"
//  Author: Walton Pelkey
//  Last Edit: 3/3/25
//  Description: C++ file defining the Fish class for Vertical Purrsuit

#include "Fish.h"
#include "EventCollision.h"
#include <LogManager.h>
#include "Score.h"
#include <WorldManager.h>
#include "EventScore.h"
#include "Platform.h"

Fish::Fish(Platform* platform) {
	setType("Fish");
	setSprite("fish");
	registerInterest(df::COLLISION_EVENT);
	registerInterest(df::STEP_EVENT);
	df::Vector platform_pos = platform->getPosition();
	float fish_x = platform_pos.getX();
	float fish_y = platform_pos.getY() - (platform->getBox().getVertical() / 2.0f) - .03; // Slightly above platform
	setPosition(df::Vector(fish_x, fish_y));
	p_platform = platform;
	LM.writeLog("Fish spawned at (%f, %f)", fish_x, fish_y);
}

// Handles events
int Fish::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast<const df::EventCollision*>(p_e);
		if (p_collision_event) {
			df::Object* p_other = (p_collision_event->getObject1() == this) ?
				p_collision_event->getObject2() :
				p_collision_event->getObject1();

			if (p_other->getType() == "Cat") {
				collect();
				return 1;
			}
		}
	}
	
	if (p_e->getType() == df::STEP_EVENT) { 
		updatePosition(); 
		return 1;
	} 
	return 0;
}

// Handles collecting the fish
void Fish::collect() {
	EventScore score_event(POINTS);
	WM.onEvent(&score_event);
	LM.writeLog("Fish collected. +%d points", POINTS); 
	WM.markForDelete(this);
}

// Updates the fish's position to be same as platform
void Fish::updatePosition() {
	if (!p_platform) {
		return;
	}
	df::Vector platform_pos = p_platform->getPosition();
	float fish_x = platform_pos.getX();
	float fish_y = platform_pos.getY() - (p_platform->getBox().getVertical() / 2.0f) - .03; // Slightly above platform
	setPosition(df::Vector(fish_x, fish_y));
}