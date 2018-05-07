#include <iostream>
#include "ControllerDevice.h"

bool ControllerDevice::Initialize()
{
	_event = new SDL_Event();
	if (!_event)
	{
		printf("SDL EVENT COULD NOT INIT!\n");
		system("pause");
		exit(1);
	}

	keyStates[GAME_DOWN] = false;
	keyStates[GAME_UP] = false;
	keyStates[GAME_LEFT] = false;
	keyStates[GAME_RIGHT] = false;
	keyStates[GAME_SPACE] = false;
	keyStates[GAME_QUIT] = false;
	keyStates[GAME_SHIFT] = false;
	Update();
	return true;
}


//====================================================
//Updates the event  based on the passed in SDL_Event
//====================================================
void ControllerDevice::Update()
{
	GAME_EVENT gEvent;
	if (SDL_PollEvent(_event))
	{
		switch (_event->type)
		{
		case SDL_KEYDOWN:
			gEvent = Translate(_event);
			keyStates.find(gEvent)->second = true;
			break;
		case SDL_KEYUP:
			gEvent = Translate(_event);
			keyStates.find(gEvent)->second = false;
			break;
		case SDL_QUIT:
			keyStates.find(GAME_QUIT)->second = true;
			break;
		default:
			break;

		}
	}
}

GAME_EVENT ControllerDevice::Translate(SDL_Event* sEvent)
{
	switch (sEvent->key.keysym.sym)
	{
	case SDLK_LEFT:
		return GAME_LEFT;
		break;
	case SDLK_RIGHT:
		return GAME_RIGHT;
		break;
	case SDLK_UP:
		return GAME_UP;
		break;
	case SDLK_DOWN:
		return GAME_DOWN;
		break;
	case SDLK_SPACE:
		return GAME_SPACE;
		break;
	case SDLK_RSHIFT:
	case SDLK_LSHIFT:
		return GAME_SHIFT;
		break;


	}
	return GAME_NA;
}

//returns the state of a key
bool ControllerDevice::GetEvent(GAME_EVENT gEvent)
{
	return (keyStates.find(gEvent)->second);
}

void ControllerDevice::Print(SDL_Event* sEvent)
{
	switch (sEvent->type)
	{
	case SDL_KEYDOWN:
		printf("SDL event type: KEYDOWN\n Key Pressed: %d\n", sEvent->key.keysym.sym);
		break;
	case SDL_KEYUP:
		printf("SDL event type: KEYUP\n Key Released: %d\n", sEvent->key.keysym.sym);
		break;
	}
}