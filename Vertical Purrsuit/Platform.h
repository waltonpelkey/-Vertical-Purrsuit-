#include "Vector.h"
#include "Object.h"
#include "EventCollision.h"

class Platform : public df::Object {
private:
	void moveToStart();
	float m_velocity;
	float v;
	int m_diff;
	void hit(const df::EventCollision *p_collision_event);
	void out();
	void step();
public:
	Platform();
	~Platform();
	int eventHandler(const df::Event* p_e) override;
};