//  File:  "EventScore.cpp"
//  Last Edit: 3/3/25
//  Description: Defines the EventScore class for Vertical Purrsuit

// Game includes
#include "EventScore.h"

// Constructor
EventScore::EventScore(int num) {
	score = num;           // Set num
	setType(SCORE_EVENT);  // Set type
}

// Getter
int EventScore::getScoreNum() const {
	return score;
}
