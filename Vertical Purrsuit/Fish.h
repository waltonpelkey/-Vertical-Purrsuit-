//  File:  "Fish.h"
//  Author: Walton Pelkey
//  Last Edit: 3/3/25
//  Description: Header file defining the Fish class for Vertical Purrsuit

#ifndef __FISH_H__
#define __FISH_H__

#include "Object.h"
#include "Platform.h"
#include "Event.h"

class Fish : public df::Object {

	const int POINTS = 100;    // point total recieved for collecting

private:
	Platform* p_platform;

public:
	Fish(Platform* platform);
	int eventHandler(const df::Event* p_e) override;
	void collect();
	void updatePosition();
};

#endif

