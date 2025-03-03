//  File:  "Score.cpp"
//  Author: Walton Pelkey
//  Last Edit: 3/3/25
//  Description: C++ file defining the Score class for Vertical Purrsuit

#include "Score.h"
#include <EventStep.h>
#include <WorldManager.h>
#include "EventScore.h"

Score::Score(Cat* cat) {
	// Set object type
	setType("Score");

	// Set default location
	setLocation(df::TOP_RIGHT);

	// Set default score to 0
	setValue(0);

	// Label
	setViewString("Score");

	// Register for step events
	registerInterest(df::STEP_EVENT);

	// Register for score events
	registerInterest(SCORE_EVENT);

	// Point to cat object
	p_cat = cat;

	// Track highest score
	highScore = 0;

	// Track number of fish caught
	fishCaught = 0;
}

// Handles events
int Score::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		updateScore();
		return 1;
	}
	if (p_e->getType() == SCORE_EVENT) {
		const EventScore* score_event = dynamic_cast<const EventScore*>(p_e);
		if (score_event) {
			int new_score = getValue() + score_event->getScoreNum();
			highScore = new_score;
			setValue(new_score);
			fishCaught++;
		}
		return 1;
	}
	return 0;
}

// Update the score based on cats height
void Score::updateScore() {
	float boundary_bottom = WM.getBoundary().getCorner().getY() + WM.getBoundary().getVertical();
	float cat_y = p_cat->getPosition().getY();
	int new_score = static_cast<int>(boundary_bottom - cat_y - 7 + (100 * fishCaught));

	if (new_score > highScore) {
		highScore = new_score;
		setValue(new_score);
	}
}