///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		ComponentAssetLibrary.h
//
//Purpose:	Store Components for quick
//			object Creation
////////////////////////////////////////

#ifndef COMPONENTASSETLIBRARY_H
#define	COMPONENTASSETLIBRARY_H

#include <map>
#include <string>
#include <vector>
#include "Define.h"

class Component;
class GameObject;

class ComponentAssetLibrary
{
public:
	ComponentAssetLibrary();
	bool Initialize();
	std::vector<Component*> Search(std::string name, GameObject* owner);
	bool AddAsset(std::string name, std::vector<GAME_COMPONENT_LIST> componentList);

	

private:
				//name				//List of components
	std::map<std::string, std::vector<GAME_COMPONENT_LIST>> componentLibrary;
};


#endif // !COMPONENTASSETLIBRARY_H
