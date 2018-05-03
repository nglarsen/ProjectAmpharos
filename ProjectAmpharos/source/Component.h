///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		Component.h
//
//Purpose:	Handle Construction & Destruction
//			of Object in the COM
////////////////////////////////////////

#ifndef COMPONENT_H
#define	COMPONENT_H

#include "GameObject.h"
#include "Define.h"

class Component
{
	Component(GameObject* owner);
	~Component();
	void OwnerDestroyed();

	GameObject* GetOwner() { return _owner; }

	virtual bool Initialize(GAME_OBJECTFACTORY_PRESETS& presets) = 0;
	virtual void Start() = 0;
	virtual GameObject* Update() = 0;
	virtual void Finish() = 0;

protected:
	GameObject* _owner;
};



#endif // !COMPONENT_H
