//  File:  "EventScore.cpp"
//  Author: Walton Pelkey
//  Last Edit: 3/3/25
//  Description: C++ file defining the EventScore class for Vertical Purrsuit

#include "EventScore.h"

EventScore::EventScore(int num) {
	score = num;
	setType(SCORE_EVENT);
}

int EventScore::getScoreNum() const {
	return score;
}
