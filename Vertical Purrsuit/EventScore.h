//  File:  "EventScore.h"
//  Author: Walton Pelkey
//  Last Edit: 3/3/25
//  Description: Header file defining the EventScore class for Vertical Purrsuit

#ifndef __EVENT_SCORE_H__
#define __EVENT_SCORE_H__

#include "Event.h"

#define SCORE_EVENT "score"

class EventScore : public df::Event {
private:
	int score; // Number of points to add
public:
	EventScore(int num);
	int getScoreNum() const;
};

#endif

