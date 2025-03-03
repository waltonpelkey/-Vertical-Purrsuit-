#include "Vector.h"
#include "Object.h"
#include "EventCollision.h"

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

class Platform : public df::Object {
private:
	void moveToStart(float y_pos);
	float m_velocity;
	float v;
	int m_diff;
	void hit(const df::EventCollision *p_collision_event);
	void out();
	void step();
public:
	Platform(float y_pos);
	~Platform();
	int eventHandler(const df::Event* p_e) override;
};

#endif