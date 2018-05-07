///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		ObjectFactory.h
//
//Purpose:	Handle the creation of
//			various objects
////////////////////////////////////////

#ifndef OBJECTFACTORY_H
#define	OBJECTFACTORY_H

#include "GameObject.h"
#include "Define.h"


class TiXmlElement;
class ResourceManager;
class Component;


class ObjectFactory
{
public:
	GameObject* Create(GAME_OBJECTFACTORY_PRESETS& presets);

};


#endif // !OBJECTFACTORY_H
