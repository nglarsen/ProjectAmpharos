///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		BodyComponent.h
//
//Purpose:	Store position and control
//			physics interactions
////////////////////////////////////////

#ifndef BODYCOMPONENT_H
#define	BODYCOMPONENT_H

#include "Component.h"

class GameObject;
class SpriteComponent;

class BodyComponent : public Component
{
public:
	BodyComponent(GameObject* owner);
	~BodyComponent();

	bool Initialize(GAME_OBJECTFACTORY_PRESETS& presets);
	void Start();
	GameObject* Update();
	void Finish();

	GAME_FLT GetAngle() { return angle; }
	ResourceManager* GetDevices() { return devices; }
	GAME_VEC GetPosition() { return oldPosition; }
	GAME_VEC GetDPosition() { return dPosition; }


protected:
	ResourceManager * devices;
	GAME_VEC dPosition;
	GAME_VEC oldPosition;
	GAME_INT angle = 0;
};


#endif // !BODYCOMPONENT_H
