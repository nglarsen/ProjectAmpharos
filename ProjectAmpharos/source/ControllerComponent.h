///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		ControllerComponent.h
//
//Purpose:	Handle User inputs
//
////////////////////////////////////////

#ifndef CONTROLLERCOMPONENT_H
#define	CONTROLLERCOMPONENT_H

#include "Component.h"
#include "Define.h"

class ResourceManager;
class ArtAssetLibrary;
class PhysicsAssetLibrary;
class ObjectFactory;

class ControllerComponent : public Component
{
	ControllerComponent(GameObject* owner);
	~ControllerComponent();

	bool Initialize(GAME_OBJECTFACTORY_PRESETS& presets);
	void SetWallHit(bool wallHit) { this->wallHit = wallHit; }

	GAME_VEC GetCurrentSquare();

	void Start();
	GameObject* Update();
	void Finish();

private:
	GAME_INT frameCount;
	ResourceManager* devices;
	GAME_PHYSICS physics;
	GAME_VEC zeroVec;
	std::map<GAME_EVENT, bool> pressControl;
	bool wallHit;
	bool noWall;
};



#endif // !CONTROLLERCOMPONENT_H
