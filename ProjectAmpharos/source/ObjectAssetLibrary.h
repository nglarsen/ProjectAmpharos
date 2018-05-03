///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		ObjectAssetLibrary.h
//
//Purpose:	Store Objects & components
//			for dynamic creation
////////////////////////////////////////

#ifndef OBJECTASSETLIBRARY_H
#define	OBJECTASSETLIBRARY_H

#include <map>
#include <string>
#include <vector>
#include "Define.h"

class GameObject;

class ObjectAssetLibrary
{
public:
	ObjectAssetLibrary();
	bool Initialize();
	GAME_OBJECT_STATS Search(std::string name);
	bool AddAsset(std::string name, GAME_OBJECT_STATS stats);

private:
	//TODO: Question this
	std::map<std::string, GAME_OBJECT_STATS> ObjectLibrary;
};



#endif // !OBJECTASSETLIBRARY_H
