//  File: "CatnipEffect.h"
//  Last Edit: 3/3/25
//  Description: Defines the CatnipEffect class for Vertical Purrsuit

#ifndef __CATNIP_EFFECT_H__
#define __CATNIP_EFFECT_H__

// System incluedes
#include <vector>
#include <SFML/Graphics.hpp>

// Engine includes
#include "Object.h"

// CatnipEffect class
// Creates a psychedelic background effect when cat collects catnip
class CatnipEffect : public df::Object {
private:
	int effectDuration;              // Duration of the effect in frames
	std::vector<df::Color> colors;   // Stores the sequence of colors for the background
	int colorIndex;                  // Tracks the current background color during the effect

public:
	// Constructor
	CatnipEffect();

	// CatnipEffect Event Handler 
	// Return 0 if ignored, else 1. 
	int eventHandler(const df::Event* p_e) override;

	// Updates the effect every frame
	void step(); 

	// Stops the effect and resets background
	void stopEffect();
};

#endif