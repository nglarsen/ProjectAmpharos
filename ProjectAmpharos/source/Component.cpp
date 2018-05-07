///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:			5/2/2018
//
//Header File:	Component.h
//
//Purpose:		
//
////////////////////////////////////////

#include "Define.h"
#include "Component.h"

Component::Component(GameObject* owner) : _owner(owner) {}

Component::~Component() {}

void Component::OwnerDestroyed()
{
	Finish();
	_owner = NULL;
}
