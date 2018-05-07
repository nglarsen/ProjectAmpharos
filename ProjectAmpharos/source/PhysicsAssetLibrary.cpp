///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:			5/2/2018
//
//Header File:	PhysicsAssetLibrary.h
//
//Purpose:		Store object specific Physics info
//
////////////////////////////////////////

#include "Define.h"
#include "PhysicsAssetLibrary.h"
#include "tinyxml\tinyxml.h"

GAME_PHYSICS PhysicsAssetLibrary::Search(std::string searchText)
{
	return(physicsLibrary.find(searchText)->second);
}

bool PhysicsAssetLibrary::Initialize()
{
	return true;
}

bool PhysicsAssetLibrary::AddAsset(std::string name, GAME_PHYSICS physics)
{
	physics.friction = 0.0f;
	physicsLibrary[name] = physics;
	return true;
}

void PhysicsAssetLibrary::Print()
{
	//dont need this
}
