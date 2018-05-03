///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		ItemBlockComponent.h
//
//Purpose:	Store Powerups and release them
//			When struck from the bottom
////////////////////////////////////////

#ifndef ITEMBLOCKCOMPONENT_H
#define	ITEMBLOCKCOMPONENT_H

#include "Component.h"
#include "Define.h"
#include "PowerUpComponent.h"
#include "Texture.h"


class ItemBlockComponent : public Component
{
	//Init open to false
	ItemBlockComponent(GameObject* owner);
	~ItemBlockComponent();
	
	//Swap texture and spawn powerup above block
	void spawnPowerUp();


	bool Initialize(GAME_OBJECTFACTORY_PRESETS& presets);
	void Start();
	
	//check open and looted, if both true call finish and delete
	GameObject* Update();
	
	//When powerup is picked up delete the block
	void Finish();
private:
	bool open;
	bool looted;
	GameObject* storedItem;
	Texture* swapTexture;

};




#endif // !ITEMBLOCKCOMPONENT_H
