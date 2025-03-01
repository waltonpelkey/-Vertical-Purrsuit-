#include "Platform.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "EventOut.h"
#include "EventStep.h"
#include "LogManager.h"

Platform::Platform() {
	m_diff = rand() % 100;
	setSprite("baseplatform");
	setSolidness(df::SOFT);
	setType("baseplatform");
	moveToStart();
	m_velocity = ((rand() % 10));
	v = m_velocity / 10;
	LM.writeLog("platform created with velocity %d and difficulty %d\n", m_velocity, m_diff);
	setVelocity(df::Vector(v, 0));
	setSolidness(df::HARD);
}

void Platform::moveToStart() {
	df::Vector temp_pos;

	float horiz = (int)DM.getHorizontal();
	float vert = (int)DM.getVertical();

	temp_pos.setX(horiz / 2);
	temp_pos.setY(vert/2);

	df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
	while (collision_list.getCount() != 0) {
		temp_pos.setX(temp_pos.getX() + 1);
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
	if (getPosition().getX() >= WM.getView().getCorner().getX() + WM.getView().getHorizontal() || getPosition().getX() <= WM.getView().getCorner().getX()) {
		setVelocity(df::Vector(v * -1, 0));
	}
}

Platform::~Platform() {
	new Platform();
}