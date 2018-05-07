#include <iostream>
#include "Timer.h"

Timer::Timer()
{
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
	mpf = 0.0f;
}

bool Timer::Intitialize(GAME_INT fps)
{
	if (fps > 0)
	{
		mpf = (GAME_FLT)1000 / fps;
		return true;
	}
	else
		return false;
}

void Timer::start()
{
	started = true;
	paused = false;
	startTicks = SDL_GetTicks();
}

void Timer::stop()
{
	started = false;
	paused = false;
}

void Timer::pause()
{
	if ((started == true) && paused == false)
	{
		paused = true;
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void Timer::unpause()
{
	if (paused == true)
	{
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}

}

Uint32 Timer::getTicks()
{
	if (started == true)
	{
		if (paused == true)
		{
			return pausedTicks;
		}
		else
		{
			return SDL_GetTicks() - startTicks;
		}
	}
	return 0;
}

bool Timer::isStarted()
{
	return started;
}

bool Timer::isPaused()
{
	return paused;
}

void Timer::fpsRegulate()
{
	if (getTicks() < mpf)
	{
		SDL_Delay((GAME_INT)mpf - getTicks());
	}
}