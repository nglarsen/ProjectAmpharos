///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:			5/2/2018
//
//Header File:	Game.h
//
//Purpose:		House the methods for running
//				And updating the game
////////////////////////////////////////

#include "Define.h"
#include "Game.h"
#include "ComponentsList.h"

//Init to null
Game::Game()
{
	devices = NULL;
	debug = false;
}

Game::~Game()
{
	if (devices)
	{
		devices->ShutDown();
		devices = NULL;
	}
}

bool Game::Initialize()
{
	//Set Game Constants

	SCREEN_WIDTH = 1024;
	SCREEN_HEIGHT = 768;
	
	return true;
}

bool Game::LoadLevel(std::string levelConfig, std::string assetConfigFile)
{
	Reset();
	//==========================
	//Construct ResourceManager
	//==========================
	devices = new ResourceManager();
	devices->Initialize(SCREEN_WIDTH, SCREEN_HEIGHT, assetConfigFile);
	this->devices = devices;

	//Get a few things ready
	GAME_OBJECTFACTORY_PRESETS presets;
	presets.devices = devices;
	ObjectFactory* objectFactory = devices->GetObjectFactory();
}


void Game::Reset()
{
	if (!objects.empty())
	{
		for (const auto object : objects)
		{
			//remove from physics world
			devices->GetPhysicsDevice()->RemoveObject(object);
		}
		//clear the vector
		objects.clear();
	}
	//kill the resource manager
	if (devices) devices->ShutDown();
	devices = NULL;
}
