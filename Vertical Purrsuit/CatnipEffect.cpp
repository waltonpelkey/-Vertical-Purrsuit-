//  File: "CatnipEffect.cpp"
//  Last Edit: 3/3/25
//  Description: Defines the CatnipEffect class for Vertical Purrsuit

// Engines includes
#include "EventStep.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "GameManager.h"
#include "ResourceManager.h"
#include "Color.h"

// Game includes
#include "CatnipEffect.h"
#include "EventCatnip.h"

// Constructor
CatnipEffect::CatnipEffect() {
	setType("CatnipEffect");            // Set type 
	setSolidness(df::SPECTRAL);         // Set as SPECTRAL to avoid any potential collisions (reduces potential bugs)
	registerInterest(df::STEP_EVENT);   // Listen for step events
	effectDuration = 90;                // Effect lasts for 90 frmaes (about 3 seconds)
	colorIndex = 0;                     // Start at the first color

	// Define rainbow colors (SFML format)
	colors = { df::RED, df::GREEN, df::BLUE, df::MAGENTA, df::CYAN }; 

	// Pla psychedelic sound effect
	RM.getSound("cat-reverb")->play();
}

// Handles events
int CatnipEffect::eventHandler(const df::Event* p_e) {
	// Check for step event
	if (p_e->getType() == df::STEP_EVENT) {
		// Try to update background every frame
		step();
		return 1;
	}
	return 0;
}

void CatnipEffect::step() {
	// Reduce timer by one frame
	effectDuration--;

	// Change the background color every few frames (so your eyes dont bleed)
	if (GM.getStepCount() % 5 == 0) {
		// Cycle through the colors
		colorIndex = (colorIndex + 1) % colors.size();
		DM.setBackgroundColor(colors[colorIndex]);

	}
	
	// Stop effect when time is up
	if (effectDuration <= 0) { 
		stopEffect(); 
		WM.markForDelete(this); 
	}
}

// Stop the effect
void CatnipEffect::stopEffect() {
	// Return to default background color
	DM.setBackgroundColor(df::WHITE);

	// End the sound effect
	RM.getSound("cat-reverb")->stop();
}

