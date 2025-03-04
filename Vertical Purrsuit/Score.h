//  File: "Score.h"
//  Last Edit: 3/3/25
//  Description: Defines the Score class for Vertical Purrsuit

#ifndef __SCORE_H__ 
#define __SCORE_H__ 

// Engine includes
#include "Event.h"
#include "ViewObject.h"

// Game includes
#include "Cat.h"

// Score class
// Tracks the players score based on height and collected fish
class Score : public df::ViewObject {
private:
	Cat* p_cat;       // Pointer to the cat object
	int highScore;    // Tracks the highest score achieved
	int fishCaught;   // Tracks the number of fish collected in a game

public:
	// Constructor
	Score(Cat* cat);

	// Handles events
	int eventHandler(const df::Event* p_e) override;

	// Updates the score as the cat moves
	void updateScore();
};

#endif

