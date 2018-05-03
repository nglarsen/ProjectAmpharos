///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		ContollerDevice.h
//
//Purpose:	Handle UserInput
//
////////////////////////////////////////

#ifndef CONTROLLERDEVICE_H
#define	CONTROLLERDEVICE_H

#include "Define.h"
#include <SDL.h>
#include <map>

class ControllerDevice
{
public:
	bool Initialize();
	void Update();
	void Print(SDL_Event* sEvent);

	bool GetEvent(GAME_EVENT gEvent);

private:
	GAME_EVENT Translate(SDL_Event* sEvent);
	SDL_Event _event;
	std::map<GAME_EVENT, bool> keyStates;
};


#endif // !CONTROLLERDEVICE_H
