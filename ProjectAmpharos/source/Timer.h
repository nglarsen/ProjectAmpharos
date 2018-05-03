///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		Timer.h
//
//Purpose:	Keep up with GameTime
//
////////////////////////////////////////

#ifndef TIMER_H
#define	TIMER_H

#include <SDL.h>
#include "Define.h"

class Timer
{
	Timer();
	bool Intitialize(GAME_INT);

	//The Various Clock Actions
	void start();
	void stop();
	void pause();
	void unpause();

	//Gets the timer's time
	GAME_INT getTicks();
	
	//Checks status of timer (On/off/paused)
	bool isStarted();
	bool isPaused();

	//You bettah Regulate
	void fpsRegulate();

private:
	//Clock time when started
	GAME_INT startTicks;
	GAME_FLT mpf; //ms per frame

	//The ticks stored when the timer was paused
	GAME_INT pausedTicks;

	//The timer status
	bool paused;
	bool started;
};


#endif // !TIMER_H

