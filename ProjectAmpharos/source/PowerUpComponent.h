///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		PowerUpComponent.h
//
//Purpose:	Control special abilities
//			Super mario world style
////////////////////////////////////////

#ifndef POWERUPCOMPONENT_H
#define	POWERUPCOMPONENT_H

#include <vector>
#include "Define.h"
#include "Component.h"

#include "Texture.h"


class PowerUpComponent : public Component
{
public:
	//Init powerLevel to 0 (or MAREEP)
	PowerUpComponent(GameObject* owner);
	~PowerUpComponent();

	bool Initialize(GAME_OBJECTFACTORY_PRESETS& presets);
	
	void Start();
	GameObject* Update();
	void Finish();

private:
	//need something to hold different sprites depending on power up
	std::vector<Texture*> evoTextures;
	//need something to dictate which power level they are at, maybe in definitions? 
	POWERUP_LEVELS powerLevel;

};



#endif // !POWERUPCOMPONENT_H

