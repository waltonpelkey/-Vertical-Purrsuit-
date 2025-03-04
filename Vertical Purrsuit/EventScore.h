//  File:  "EventScore.h"
//  Last Edit: 3/3/25
//  Description: Defines the EventScore class for Vertical Purrsuit

#ifndef __EVENT_SCORE_H__
#define __EVENT_SCORE_H__

// Engine includes
#include "Event.h"

// Event label
#define SCORE_EVENT "score"

// Event to alert Score to update
class EventScore : public df::Event {
private:
	int score; // Number of points to add

public:
	// Constructor
	EventScore(int num);

	// Getter
	int getScoreNum() const;
};

#endif

