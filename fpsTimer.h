//
//  FpsTimer.hpp
//  amethyst_engine
//
//  Created by Albert Bode on 5/24/17.
//  Copyright © 2017 Albert Bode. All rights reserved.
//

#ifndef FpsTimer_hpp
#define FpsTimer_hpp

#include <stdio.h>
#include <ctime>
#include <deque>

class FpsTimer
{
private :
	std::deque<float> *lastFrameTimes;
	time_t lastFrame, tempTime;
	char *fpsString;
	int averageOfFrames;
	int framesToUpdate;
	float averageFps;
public :
	FpsTimer(int averageOfFrames);
	void timeFrame();
	char *getFps();
};

#endif /* FpsTimer_h */
