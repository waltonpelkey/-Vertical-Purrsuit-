//  File:  "Score.h"
//  Author: Walton Pelkey
//  Last Edit: 3/3/25
//  Description:  Header file defining the Score class for Vertical Purrsuit

#ifndef __SCORE_H__ 
#define __SCORE_H__ 

#include "Event.h"
#include "ViewObject.h"
#include "Cat.h"

class Score : public df::ViewObject {
private:
	Cat* p_cat;
	int highScore;
	int fishCaught;

public:
	Score(Cat* cat);
	int eventHandler(const df::Event* p_e) override;
	void updateScore();
};

#endif

