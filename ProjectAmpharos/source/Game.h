///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		Game.h
//
//Purpose:	House the methods for running
//			and updating the game
////////////////////////////////////////

#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include "Define.h"
#include "ResourceManager.h"

#include "ArtAssetLibrary.h"
#include "PhysicsAssetLibrary.h"

#include "ObjectFactory.h"

#include "View.h"
#include "Timer.h"

#include "tinyxml\tinyxml.h"



class Game 
{
public:
	Game();
	~Game();
	bool Initialize();
	void Reset();
	bool LoadLevel(std::string levelConfig, std::string assetConfig);
	bool Run();
	void Update();
	void Draw();

private:
	std::vector<GameObject*> objects;
	std::vector<GameObject*> newObjects;

	ResourceManager* devices;
	GAME_FLT gameTime;
	bool debug;
	GAME_INT SCREEN_WIDTH;
	GAME_INT SCREEN_HEIGHT;
};


#endif //GAME_H
