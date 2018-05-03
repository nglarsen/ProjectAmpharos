#include <iostream>

//Resource Manager for device calls
#include "ResourceManager.h"

//Game for running the game
#include "Game.h"

//constants
#include "Define.h"

void pause() { system("pause"); }

int main()
{
	//===============
	//Make the Game
	//===============
	Game* game = new Game();
	
	if (!game->Initialize())
	{
		printf("Game could not init\n");
		pause();
		exit(1);
	}
	//===============
	//Load Level
	//===============
	std::string assetFile = "./Assets/Config/MainAssets.xml";
	std::string levelConfigFile = "./Assets/Config/levelList.xml";
	//Multilevel construction:
	//XML File for levels read through until level == xmlelement->value().  Set the xml doc to that sheet then load the level from there.
	if (!game->LoadLevel(levelConfigFile, assetFile))
	{
		printf("Level could not init\n");
		pause();
		exit(1);
	}
	//===============
	//Main Game loop
	//===============
	while (game->Run()) {}
	if (game)
	{
		game = NULL;
	}

	return 0;
}