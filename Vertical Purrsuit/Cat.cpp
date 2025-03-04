//  File: "Cat.cpp"
//  Last Edit: 3/3/25
//  Description: Defines the Cat class for Vertical Purrsuit

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
#include "DisplayManager.h"

// Game includes
#include "Cat.h"
#include "EventCatnip.h"
#include "CatnipEffect.h"

// Constructor
Cat::Cat() {
	setSprite("cat-idle");			// Default sprite
	setType("Cat");					// Set object type
	setVelocity(df::Vector(0, 0));  // Start staionary

	// Register for events
	registerInterest(df::STEP_EVENT);
	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::OUT_EVENT);

	// Initialize states
	isAlive = true;
	isGrounded = false;
	isCatnipActive = false;
	catnip_timer = 0;

	// Draw the cat above other objects
	setAltitude(1);

	// Camera follows the cat
	WM.setViewFollowing(this);

	// Play background music
	RM.getMusic("background-music")->play();
}

// Destructor for cat class
// Will need to be updated when we make a game over screen
Cat::~Cat() {}

// TMove the cat to the starting position
int Cat::moveToStart() {
	// Get world boundaries for reference
	float world_horiz = WM.getBoundary().getHorizontal();
	float world_vert = WM.getBoundary().getVertical();

	// Temporary return variable
	df::Vector temp_pos;

	// Start at the center bottom of the world
	temp_pos.setX(world_horiz / 2.0f);
	temp_pos.setY(world_vert - 7.7);
	WM.moveObject(this, temp_pos);

	// Return success
	return 0;
}

// Calculate the cat's Y velocity given constant gravity
df::Vector Cat::gravityUpdate() {
	// Cap falling speed to a constant value
	if (getVelocity().getY() >= MAX_Y) {
		return getVelocity();
	}
	// Else return current velocity plus gravity
	return df::Vector(getVelocity().getX(), getVelocity().getY() + GRAVITY);
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

// Cat Event Handler
// Return 0 if ignored, else 1.
int Cat::eventHandler(const df::Event* p_e) {
	// Check for keyboard event
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event = dynamic_cast <const df::EventKeyboard*> (p_e);
		if (p_keyboard_event) {
			kbd(p_keyboard_event);
		}
		return 1;
	}

	// Check for step event
	if (p_e->getType() == df::STEP_EVENT) {
		const df::EventStep* p_step_event = dynamic_cast<const df::EventStep*>(p_e);
		// On the first step, move to start position
		if (p_step_event && p_step_event->getStepCount() == 0) {
			moveToStart();
		}
		// Call step function
		step();
		return 1;
	}

	// Check for out event
	if (p_e->getType() == df::OUT_EVENT) {
		const df::EventOut* p_step_event = dynamic_cast<const df::EventOut*>(p_e);
		out();
	}

	// Check for collision event
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast<const df::EventCollision*>(p_e);
		collision(p_collision_event);
	}

	// Check for catnip event
	if (p_e->getType() == CATNIP_EVENT) {
		// Trigger catnip state
		isCatnipActive = true;

		// Start frame counter
		catnip_timer = 200;

		// Set Y velocity to launch upwards
		setVelocity(df::Vector(getVelocity().getX(), -2.5));
		return 1;
	}
	return 0;
}

// Run on each frame to update physics
void Cat::step() {
	// Handle catnip effects
	if (isCatnipActive) {
		// Count down one frame
		catnip_timer--;

		// Reset effect when timer ends
		if (catnip_timer <= 0) {
			isCatnipActive = false;
		}
	}

	// Only apply gravity when off the ground or not on a platform
	if (!isGrounded) {
		setVelocity(gravityUpdate()); 

		// If you're not grounded then you're not on a platform
		platformCollision = false;
	}

	// If on a platform, keep the cat centered
	else if (currentPlatform) {
		setPosition(df::Vector(currentPlatform->getPosition().getX(), currentPlatform->getPosition().getY() - (getBox().getVertical() / 2.0f)));
	}

	// If on the ground apply friction
	if (isGrounded) {
		// If the cat is slow enough to come to a complete stop then do so
		if (( - X_FRICTION < getVelocity().getX() && getVelocity().getX() < 0) || (X_FRICTION > getVelocity().getX() && getVelocity().getX() > 0)) {
			setVelocity(df::Vector(0, getVelocity().getY())); 

			// Return to avoid adding more friction which would result in reversing your movement
			return;
		}

		// Apply friction to slow the cat
		setVelocity(frictionUpdate());
	}

	// Assign appropriate sprite based on state of velocity
	assignSprite();

	// Ensure cat does not exceed speed limit in x direction
	if (getVelocity().getX() > X_SPEED_RIGHT) { 
		// Reset speed to max speed
		setVelocity(Vector(X_SPEED_RIGHT, this->getVelocity().getY()));
	}

	// Ensure cat does not exceed speed limit in x direction
	else if (getVelocity().getX() < X_SPEED_LEFT) {
		// Reset the speed to min speed
		setVelocity(Vector(X_SPEED_LEFT, this->getVelocity().getY()));
	}

	// Reset isGrounded if the cat's y velocity is not 0
	if (this->getVelocity().getY() != 0) {
		// If the cat has a non-zero Y velocity it is not standing
		isGrounded = false;

		// If the cat has a non-zero Y velocity is is not attached to a platform
		currentPlatform = nullptr;
	}
}

// Take appropriate action according to key pressed
void Cat::kbd(const df::EventKeyboard* p_keyboard_event) {
	// Ensure that the pointer is not null to avoid null reference
	if (!p_keyboard_event) return;

	// Switch for keys used in game
	switch (p_keyboard_event->getKey()) {
	// SPACE -> Jump
	case df::Keyboard::SPACE:
		// Ensure no double jump
		if (!isGrounded) {
			break;
		}

		// Set so that game over can be called
		hasJumped = true;

		// If key was pressed then perform jump
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			// Set new Y velocity to jump
			setVelocity(df::Vector(getVelocity().getX(), -JUMP));

			// Randomly choose a jump audio
			int randSound = (rand() % 4) + 1;
			switch (randSound) {
			case 1:
				RM.getSound("meow-1")->play();
				break;
			case 2:
				RM.getSound("meow-2")->play();
				break;
			case 3:
				RM.getSound("meow-3")->play();
				break;
			case 4:
				RM.getSound("meow-4")->play();
				break;
			}
		}
		break;

	// W -> Jump
	case df::Keyboard::W: 
		// Ensure no double jump
		if (!isGrounded) {
			break;
		}

		// Set so that game over can be called
		hasJumped = true;

		// If key was pressed then perform jump
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			// Set new Y velocity to jump
			setVelocity(df::Vector(getVelocity().getX(), -JUMP));

			// Randomly choose a jump audio
			int randSound = (rand() % 4) + 1;
			switch (randSound) {
			case 1:
				RM.getSound("meow-1")->play();
				break;
			case 2:
				RM.getSound("meow-2")->play();
				break;
			case 3:
				RM.getSound("meow-3")->play();
				break;
			case 4:
				RM.getSound("meow-4")->play();
				break;
			}
		}
		break;

	// A -> Move left
	case df::Keyboard::A:
		// If key was pressed then move left
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			// Set new x velocity to move
			setVelocity(df::Vector(getVelocity().getX() - SIDEWAYS_MOVEMENT, getVelocity().getY()));
		}
		break;

	// LEFT ARROW -> Move left
	case df::Keyboard::LEFTARROW: 
		// If key was pressed then move left
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			// Set new x velocity to move
			setVelocity(df::Vector(getVelocity().getX() - SIDEWAYS_MOVEMENT, getVelocity().getY()));
		}
		break;

	// D -> Move right
	case df::Keyboard::D: 
		// If key was pressed then move right
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			// Set new x velocity to move
			setVelocity(df::Vector(getVelocity().getX() + SIDEWAYS_MOVEMENT, getVelocity().getY()));
		}
		break;

	// RIGHT ARROW -> Move right
	case df::Keyboard::RIGHTARROW:
		// If key was pressed then move right
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED) {
			// Set new x velocity to move
			setVelocity(df::Vector(getVelocity().getX() + SIDEWAYS_MOVEMENT, getVelocity().getY()));
		}
		break;
	default: // Input key doesnt do anything
		return;
	};
	return;
}

// Wrap cat around to opposite side of world view
void Cat::out() {
	// Check if out event was on the right
	if (getPosition().getX() >= WM.getView().getHorizontal()) {
		setPosition(df::Vector(0, getPosition().getY()));
	}
	// Out event was on the left
	else if (getPosition().getX() <= 0) {
		setPosition(df::Vector(WM.getView().getHorizontal(), getPosition().getY()));
	}
}

// Handle collision event
void Cat::collision(const df::EventCollision* p_e) {
	// Assign p_other to the object in the collision that is not yourself
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
		// Find the boundaries of cat and platform to help determine collision type
		float cat_top = getPosition().getY() - (getBox().getVertical() / 2.0f);
		float cat_bottom = getPosition().getY() + (getBox().getVertical() / 2.0f);
		float cat_left = getPosition().getX() - (getBox().getHorizontal() / 2.0f);
		float cat_right = getPosition().getX() + (getBox().getHorizontal() / 2.0f);
		float platform_top = p_other->getPosition().getY() - (p_other->getBox().getVertical() / 2.0f);
		float platform_bottom = p_other->getPosition().getY() + (p_other->getBox().getVertical() / 2.0f);
		float platform_left = p_other->getPosition().getX() - (p_other->getBox().getHorizontal() / 2.0f);
		float platform_right = p_other->getPosition().getX() + (p_other->getBox().getHorizontal() / 2.0f);
		
		// If the cat is below the platform then ignore collision
		if (cat_top >= platform_bottom) {
			return;
		}

		// If cat is above platform (with some lee-way) then center the cat on the platform
		if (cat_bottom <= platform_top && cat_right >= platform_left - 0.0005 && cat_left <= platform_right + 0.0005) {
			// Stop downward movement
			setVelocity(df::Vector(0, 0));

			// Center the cat horizontally on the platform
			setPosition(df::Vector(p_other->getPosition().getX(), platform_top - (getBox().getVertical() / 2.0f)));

			// Set grounded to true since you're standing on a platform
			isGrounded = true;

			// Store platform reference for later checks
			currentPlatform = p_other;

			// Play grounded sound only if it's a new platform
			if (currentPlatform != lastPlatform) {
				// Ensure that the next time a collision is registered to center you that you do not repeat the sound
				lastPlatform = currentPlatform;

				// Play a randomly chosen platform collision sound
				int randSound = (rand() % 4) + 1;
				switch (randSound) {
				case 1:
					RM.getSound("grounded-1")->play();
					break;
				case 2:
					RM.getSound("grounded-2")->play();
					break;
				case 3:
					RM.getSound("grounded-3")->play();
					break;
				case 4:
					RM.getSound("grounded-4")->play();
					break;
				}
			}
		}
	}

	// Check for collision with catnip
	if (p_other->getType() == "Catnip") {
		// Set velocity to catnip state
		setVelocity(df::Vector(getVelocity().getX(), -3.0f));

		// Create new catnip effect object 
		new CatnipEffect();

		// Delete the catnip object after colliding
		WM.markForDelete(p_other);
	}

}

// If cat is grounded account for friction
df::Vector Cat::frictionUpdate() {
	float y_veloc = getVelocity().getY();
	float x_veloc = getVelocity().getX();

	// Apply friction opposite of movement
	if (x_veloc > 0) {
		x_veloc -= X_FRICTION;
	}
	if (x_veloc < 0) {
		x_veloc += X_FRICTION;
	}

	// Return new velocity
	return df::Vector(x_veloc, y_veloc);
}