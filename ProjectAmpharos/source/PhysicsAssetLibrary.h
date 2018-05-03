///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		PhysicsAssetLibrary.h
//
//Purpose:	Allow for dynamic creation
//			and deletion of objects with
//			consistent physical 
//			properties
////////////////////////////////////////

#ifndef PHYSICSASSETLIBRARY_H
#define	PHYSICSASSETLIBRARY_H

#include <string>
#include <map>
#include <iostream>

#include "Define.h"

class PhysicsAssetLibrary 
{
public:
	void Print();
	GAME_PHYSICS Search(std::string name);

	bool Initialize();
	bool AddAsset(std::string name, GAME_PHYSICS physics);

protected:
	std::map<std::string, GAME_PHYSICS> physicsLibrary;
};


#endif // !PHYSICSASSETLIBRARY_H
