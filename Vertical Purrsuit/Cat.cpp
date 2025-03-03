//  File:  "Cat.cpp"
//  Author: Walton Pelkey
//  Last Edit: 2/28/25
//  Description:  C++ file defining the Cat class for Vertical Purrsuit

// System includes
#include <string>

// Engine includes
#include "LogManager.h"
#include "Object.h" 
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Vector.h"
#include "Event.h"
#include "EventStep.h"
#include "EventOut.h"
#include "EventCollision.h"

// Game includes
#include "Cat.h"
#include <DisplayManager.h>


// Constructor for cat class
Cat::Cat() {
	// Set sprite to cat sprite
	setSprite("cat-dropping-left");

	// Set object type to Cat
	setType("Cat");

	// Set initial velocity to (0,0)
	setVelocity(df::Vector(0, 0));

	// Need to update the physics
	registerInterest(df::STEP_EVENT);

	// Need for the cat to jump
	registerInterest(df::KEYBOARD_EVENT);

	// Need for the wrap around
	registerInterest(df::OUT_EVENT);

	// Set alive to true
	isAlive = true;

	// Set double jump to false
	isDoubleJump = false;

	// Set view to follow cat
	WM.setViewFollowing(this);

	// Set grounded to false
	isGrounded = false;

	setAltitude(1);
}

// Destructor for cat class
Cat::~Cat() {}

// This function sets the initial position of the cat 
int Cat::moveToStart() {
	df::Vector temp_pos;

	// Get world boundaries
	float world_horiz = WM.getBoundary().getHorizontal();
	float world_vert = WM.getBoundary().getVertical();

	// X is centered on window
	temp_pos.setX(world_horiz / 2.0f);

	// Y is at bottom of window
	temp_pos.setY(world_vert - 7.7);

	WM.moveObject(this, temp_pos);

	// If successful 
	return 0;
}

// This function determines the appropriate sprite for the cat
void Cat::assignSprite() {
	// Get cat y velocity
	float y_veloc = this->getVelocity().getY();
	// Get cat x velocity
	float x_veloc = this->getVelocity().getX();

	// If x velocity is more than 0
	if (isGrounded && x_veloc > 0) {
		std::string sprite = "cat-walking-right";
		if (this->getAnimation().getSprite()->getLabel() == sprite) {
			return;
		}
		this->setSprite(sprite);
		Animation animation;
		animation.setSprite(RM.getSprite(sprite));
		this->setAnimation(animation);
		return;
	}

	// If x velocity is less than 0
	else if (isGrounded && x_veloc < 0) {
		std::string sprite = "cat-walking-left";
		if (this->getAnimation().getSprite()->getLabel() == sprite) {
			return;
		}
		this->setSprite(sprite);
		Animation animation;
		animation.setSprite(RM.getSprite(sprite));
		this->setAnimation(animation);
		return;
	}

	// If y velocity is more than 0
	if (y_veloc > 0) {
		// If x direction more than 0
		if (x_veloc > 0) {
			std::string sprite = "cat-dropping-right";
			if (this->getAnimation().getSprite()->getLabel() == sprite) {
				return;
			}
			this->setSprite(sprite);
			Animation animation;
			animation.setSprite(RM.getSprite(sprite));
			this->setAnimation(animation);
			return;
		}
		// If x direction less than or equal to 0
		else {
			std::string sprite = "cat-dropping-left";
			if (this->getAnimation().getSprite()->getLabel() == sprite) {
				return;
			}
			this->setSprite(sprite);
			Animation animation;
			animation.setSprite(RM.getSprite(sprite));
			this->setAnimation(animation);
			return;
		}
	}

	// If y velocity is less than 0
	else if (y_veloc < 0) {
		// If x direction more than 0
		if (x_veloc > 0) {
			std::string sprite = "cat-rising-right";
			if (this->getAnimation().getSprite()->getLabel() == sprite) {
				return;
			}
			this->setSprite(sprite);
			Animation animation;
			animation.setSprite(RM.getSprite(sprite));
			this->setAnimation(animation);
			return;
		}
		// If x direction less than or equal to 0
		else {
			std::string sprite = "cat-rising-left";
			if (this->getAnimation().getSprite()->getLabel() == sprite) {
				return;
			}
			this->setSprite(sprite);
			Animation animation;
			animation.setSprite(RM.getSprite(sprite));
			this->setAnimation(animation);
			return;
		}
	}

	// Else return "cat-idle"
	else {
		std::string sprite = "cat-idle";
		if (this->getAnimation().getSprite()->getLabel() == sprite) {
			return;
		}
		this->setSprite(sprite);
		Animation animation;
		animation.setSprite(RM.getSprite(sprite));
		this->setAnimation(animation);
		return;
	}
}

// This function calculates the new velocity of the cat based on physics
df::Vector Cat::gravityUpdate() {
	if (this->getVelocity().getY() >= MAX_Y) {
		return this->getVelocity(); 
	}
	float y_veloc = this->getVelocity().getY();
	float x_veloc = this->getVelocity().getX();
	y_veloc = y_veloc + GRAVITY;
	df::Vector new_vector = df::Vector(x_veloc, y_veloc);

	return new_vector;
}

// Cat Event Handler
// Return 0 if ignored, else 1.
int Cat::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event = dynamic_cast <const df::EventKeyboard*> (p_e);
		if (p_keyboard_event) {
			kbd(p_keyboard_event);
		}
		return 1;
	}
	if (p_e->getType() == df::STEP_EVENT) {
		const df::EventStep* p_step_event = dynamic_cast<const df::EventStep*>(p_e);
		// On the first step, move to start position
		if (p_step_event && p_step_event->getStepCount() == 0) {
			moveToStart();
		}
		step();
		return 1;
	}
	if (p_e->getType() == df::OUT_EVENT) {
		const df::EventOut* p_step_event = dynamic_cast<const df::EventOut*>(p_e);
		out();
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast<const df::EventCollision*>(p_e);
		collision(p_collision_event);
	}
	return 0;
}

// Run on each frame
void Cat::step() {

	// Only apply gravity when off the ground
	if (!isGrounded) {
		df::Vector vector = gravityUpdate();
		this->setVelocity(vector);
		platformCollision = false;
	}
	else if (currentPlatform) {
		// If on a platform, keep the cat centered
		float new_x = currentPlatform->getPosition().getX();
		float new_y = currentPlatform->getPosition().getY() - (this->getBox().getVertical() / 2.0f);
		this->setPosition(df::Vector(new_x, new_y));
	}

	// If on the ground apply friction
	if (isGrounded) {
		// If the cat is slwo enough to come to a complete stop then do so
		if (-X_FRICTION < this->getVelocity().getX() && this->getVelocity().getX() < 0) {
			this->setVelocity(df::Vector(0, this->getVelocity().getY()));
			return;
		}
		// If the cat is slow enough to come to a complete stop then do so
		else if (X_FRICTION > this->getVelocity().getX() && this->getVelocity().getX() > 0) {
			this->setVelocity(df::Vector(0, this->getVelocity().getY()));
			return;
		}

		// Apply friction to slow the cat
		df::Vector vector = frictionUpdate();
		this->setVelocity(vector);
	}

	// Assign appropriate sprite based on state of velocity
	assignSprite();

	// Ensure cat does not exceed speed limit in x direction
	if (this->getVelocity().getX() > X_SPEED_MAX) {
		this->setVelocity(Vector(X_SPEED_MAX, this->getVelocity().getY()));
	}

	// Ensure cat does not exceed speed limit in x direction
	else if (this->getVelocity().getX() < X_SPEED_MIN) {
		this->setVelocity(Vector(X_SPEED_MIN, this->getVelocity().getY()));
	}

	// Reset isGrounded if the cat's y velocity is not 0
	if (this->getVelocity().getY() != 0) {
		isGrounded = false;
		currentPlatform = nullptr;
	}
}

// Take appropriate action according to key pressed
void Cat::kbd(const df::EventKeyboard* p_keyboard_event) {
	if (!p_keyboard_event) return;

	switch (p_keyboard_event->getKey()) {
	case df::Keyboard::SPACE: // Jump
		if (!isGrounded) {
			break;
		}
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			this->setVelocity(df::Vector(this->getVelocity().getX(), -JUMP));
			hasJumped = true;
		}
		break;
	case df::Keyboard::W: // Jump
		if (!isGrounded) {
			break;
		}
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			this->setVelocity(df::Vector(this->getVelocity().getX(), -JUMP));
			hasJumped = true;
		}
		break;
	case df::Keyboard::A: // Move left
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			this->setVelocity(df::Vector(this->getVelocity().getX() - SIDEWAYS_MOVEMENT, this->getVelocity().getY()));
		}
		break;
	case df::Keyboard::LEFTARROW: // Move left
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			this->setVelocity(df::Vector(this->getVelocity().getX() - SIDEWAYS_MOVEMENT, this->getVelocity().getY()));
		}
		break;
	case df::Keyboard::D: // Move right
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			this->setVelocity(df::Vector(this->getVelocity().getX() + SIDEWAYS_MOVEMENT, this->getVelocity().getY()));
		}
		break;
	case df::Keyboard::RIGHTARROW: // Move right
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			this->setVelocity(df::Vector(this->getVelocity().getX() + SIDEWAYS_MOVEMENT, this->getVelocity().getY()));
		}
		break;
	default: // key doesnt do anything
		return;
	};

	return;
}

// Wrap cat around to opposite side of world view
void Cat::out() {
	// Check if out event was on the right
	if (this->getPosition().getX() >= WM.getView().getHorizontal()) {
		this->setPosition(df::Vector(0, this->getPosition().getY()));
	}
	// Out event was on the left
	else if (this->getPosition().getX() <= 0) {
		this->setPosition(df::Vector(WM.getView().getHorizontal(), this->getPosition().getY()));
	}
}

void Cat::collision(const df::EventCollision* p_e) {
	df::Object* p_other;
	if (p_e->getObject1() == this) {
		p_other = p_e->getObject2();
	}
	else {
		p_other = p_e->getObject1();
	}

	// Check for collision with Floor
	if (p_other->getType() == "Floor") {
		// Check that cat is above the platform
		if (this->getPosition().getY() < p_other->getPosition().getY()) {
			// Stop downward movement
			setVelocity(df::Vector(this->getVelocity().getX(), 0));

			// Set grounded to true
			isGrounded = true;
		}
	}

	// Check for collision with Platform
	else if (p_other->getType() == "baseplatform") {
		float cat_top = this->getPosition().getY() - (this->getBox().getVertical() / 2.0f);  
		float cat_bottom = this->getPosition().getY() + (this->getBox().getVertical() / 2.0f);
		float platform_top = p_other->getPosition().getY() - (p_other->getBox().getVertical() / 2.0f);
		float platform_bottom = p_other->getPosition().getY() + (p_other->getBox().getVertical() / 2.0f);  
		float platform_left = p_other->getPosition().getX() - (p_other->getBox().getHorizontal() / 2.0f);
		float platform_right = p_other->getPosition().getX() + (p_other->getBox().getHorizontal() / 2.0f);
		float cat_left = this->getPosition().getX() - (this->getBox().getHorizontal() / 2.0f);
		float cat_right = this->getPosition().getX() + (this->getBox().getHorizontal() / 2.0f);
		
		if (cat_top >= platform_bottom) {
			return;
		}
		// If cat is above platform
		if (cat_bottom <= platform_top && cat_right >= platform_left - 0.0005 && cat_left <= platform_right + 0.0005) {
			// Stop downward movement
			setVelocity(df::Vector(0, 0));

			// Center the cat horizontally on the platform
			float new_x = p_other->getPosition().getX();
			float new_y = platform_top - (this->getBox().getVertical() / 2.0f);
			this->setPosition(df::Vector(new_x, new_y));

			// Set grounded to true
			isGrounded = true;

			// Store platform reference for later checks
			currentPlatform = p_other;   
		}
	}

}

// If cat is grounded account for friction
df::Vector Cat::frictionUpdate() {
	float y_veloc = this->getVelocity().getY();
	float x_veloc = this->getVelocity().getX();

	// Apply friction opposite of movement
	if (x_veloc > 0) {
		x_veloc -= X_FRICTION;
	}
	if (x_veloc < 0) {
		x_veloc += X_FRICTION;
	}

	// Return new velocity
	df::Vector new_vector = df::Vector(x_veloc, y_veloc);
	return new_vector;
}