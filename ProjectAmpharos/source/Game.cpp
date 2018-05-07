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
	
	//=========================================
	//Load all the files
	//=========================================

	TiXmlDocument currentLevel(levelConfig);

	if (!currentLevel.LoadFile()) { return false; }

	TiXmlElement* levelRoot = currentLevel.FirstChildElement();
	TiXmlElement* levelObject = levelRoot->FirstChildElement();

	GAME_INT squareDimension = 16;
	presets.position.x = 0;
	presets.position.y = 0;

	GAME_VEC squarePosition = { presets.position.x, presets.position.y };

	do
	{
		std::string objectName;
		int xPos, yPos;

		levelObject->QueryStringAttribute("name", &presets.objectType);
		levelObject->QueryFloatAttribute("xPos", &presets.position.x);
		levelObject->QueryFloatAttribute("yPos", &presets.position.y);
		
		if (presets.objectType == "Player")
		{
			GAME_INT halfWidth = devices->GetGraphicsDevice()->GetScreenWidth() / 2;
			GAME_INT halfHeight = devices->GetGraphicsDevice()->GetScreenHeight() / 2;

			squarePosition.x = presets.position.x*(-1) + halfWidth;
			squarePosition.x = presets.position.y*(-1) + halfHeight;

			devices->SetCityCorner(squarePosition);

			presets.position.x = halfWidth;
			presets.position.y = halfHeight;
		}
		GameObject* newObject = objectFactory->Create(presets);
		objects.push_back(newObject);

		presets.position = squarePosition;

		levelObject =	levelObject->NextSiblingElement();
	} while (levelObject);

	devices->GetSoundDevice()->SetBackground("main");

	return true;
}

bool Game::Run()
{
	if (devices->GetControllerDevice()->GetEvent(GAME_QUIT) == true)
	{
		return false;
	}

	//Poll for new events
	devices->GetControllerDevice()->Update();

	//Construct frame timer
	Timer* frameRate = new Timer();
	if (!frameRate->Intitialize(devices->GetGAME_FPS())) { exit(1); }
	frameRate->start();

	Update();
	Draw();

	frameRate->fpsRegulate();
	return true;
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

void Game::Update()
{
	//update the physics world
	devices->GetPhysicsDevice()->Update(2.0f / devices->GetGAME_FPS());

	std::vector<GameObject*>::iterator objectIter;
	for (int i = 0; i<(int)objects.size(); i++)
	{
		objects[i]->Update();
	}
	if (!newObjects.empty())
	{
		objects.insert(objects.end(), newObjects.begin(), newObjects.end());
		newObjects.clear();
	}

	for (auto object : objects)
	{
		GameObject* temp = object->Update();
		if (temp != NULL)
		{
			newObjects.push_back(temp);
		}
	}
}

void Game::Draw()
{
	devices->GetGraphicsDevice()->Begin();
	devices->GetGraphicsDevice()->Draw();

	if (debug)devices->GetPhysicsDevice()->getWorld()->DrawDebugData();
	devices->GetGraphicsDevice()->Present();
}
