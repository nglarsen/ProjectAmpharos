///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:			5/2/2018
//
//Header File:	ComponentAssetLibrary.h
//
//Purpose:		Store object specific Component info
//
////////////////////////////////////////

#include "ComponentAssetLibrary.h"
#include "ComponentsList.h"
#include "ControllerComponent.h"

ComponentAssetLibrary::ComponentAssetLibrary() {}

bool ComponentAssetLibrary::Initialize()
{
	return true;
}

std::vector<Component*> ComponentAssetLibrary::Search(std::string name, GameObject* owner)
{
	std::vector<Component*> componentListPtrs;

	std::vector<GAME_COMPONENT_LIST> componentList = componentLibrary.find(name)->second;

	for (auto comp : componentList)
	{
		switch (comp)
		{
		case GAME_BODY_COMP:
			componentListPtrs.push_back(new BodyComponent(owner));
			break;
		case GAME_SPRITE_COMP:
			componentListPtrs.push_back(new SpriteComponent(owner));
			break;
		case GAME_CONTROL_COMP:
			componentListPtrs.push_back(new ControllerComponent(owner));
			break;
		case GAME_ITEMBLOCK_COMP:
			componentListPtrs.push_back(new ItemBlockComponent(owner));
			break;
		case GAME_POWERUP_COMP:
			componentListPtrs.push_back(new PowerUpComponent(owner));
			break;
		default:
			break;
		}
	}
	return componentListPtrs;
}

bool ComponentAssetLibrary::AddAsset(std::string name, std::vector<GAME_COMPONENT_LIST> componentList)
{
	componentLibrary[name] = componentList;
	return true;
}