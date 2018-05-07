///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:			5/2/2018
//
//Header File:	ObjectFactory.h
//
//Purpose:		Create objects
//
////////////////////////////////////////

#include "ObjectFactory.h"
#include "ComponentsList.h"
#include "Define.h"

GameObject* ObjectFactory::Create(GAME_OBJECTFACTORY_PRESETS& presets)
{
	GameObject* newObject = new GameObject();
	
	ComponentAssetLibrary* componentLibrary;
	
	std::vector<Component*> componentList = presets.devices->GetComponentAssetLibrary()->Search(presets.objectType, newObject);


	for (auto comp : componentList)
	{
		newObject->AddComponent(comp);
	}

	if (newObject->Initialize(presets))
	{
		return newObject;
	}
	else
	{
		printf("Object did not initialize\n");
		return NULL;
	}
}