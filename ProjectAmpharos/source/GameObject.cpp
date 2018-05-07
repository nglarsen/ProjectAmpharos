///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:			5/2/2018
//
//Header File:	GameObject.h
//
//Purpose:		Be a gameObject
//
////////////////////////////////////////

#include "Define.h"
#include "GameObject.h"

GameObject::GameObject()
{
	initialized = false;
}

GameObject::~GameObject()
{

}

bool GameObject::Initialize(GAME_OBJECTFACTORY_PRESETS& presets)
{
	objectType = presets.objectType;
	
	SpriteComponent* component = GetComponent<SpriteComponent>();
	if (component) component->Initialize(presets);

	//init all components
	for (auto comp : components)
	{
		comp->Initialize(presets);
	}

	if (!initialized)
	{
		for (auto comp : components)
		{
			comp->Start();
		}
		initialized = true;
	}
	return true;
}

void GameObject::AddComponent(Component* component)
{
	components.push_back(component);
}

GameObject* GameObject::Update()
{
	GameObject* newObject = NULL;
	for (auto comp : components)
	{
		GameObject* tempObject = NULL;
		tempObject = comp->Update();
		if (tempObject != NULL)
		{
			newObject = tempObject;
		}
	}
	return newObject;
}

bool GameObject::removeComponents()
{
	for (auto comp : components)
	{
		comp->Finish();
	}
	components.clear();
	return true;
}