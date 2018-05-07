////////////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		GameObject.h
//
//Purpose:	Handle creation of individual
//			objects and attaching components
/////////////////////////////////////////////

#ifndef GAMEOBJECT_H
#define	GAMEOBJECT_H

#include <memory>
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Define.h"
#include "ComponentsList.h"

class Component;
class GraphicsDevice;
class PhysicsDevice;

class GameObject
{
public:
	GameObject();
	~GameObject();

	bool Initialize(GAME_OBJECTFACTORY_PRESETS& presets);
	void AddComponent(Component* component);

	template<class T>
	T* GetComponent()
	{
		for (auto comp : components)
		{
			T* target = nullptr;
			if (target = dynamic_cast<T*>(comp))
			{
				return(target);
			}
		}
		return(nullptr);
	}

	GameObject* Update();

	void SetJoinedWith(GameObject* joinedWith) { this->joinedWith = joinedWith; }

	std::string getObjectType() { return objectType; }
	GameObject* GetJoinedWith() { return joinedWith; }

	bool removeComponents();

protected:
	std::vector<Component*> components;
	bool initialized;
	std::string objectType;
	GameObject* joinedWith;
};



#endif // GAMEOBJECT_H
