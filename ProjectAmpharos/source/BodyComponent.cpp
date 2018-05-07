///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:			5/2/2018
//
//Header File:	BodyComponent.h
//
//Purpose:		
//
////////////////////////////////////////

#include "Define.h"
#include "BodyComponent.h"
#include "GameObject.h"

BodyComponent::BodyComponent(GameObject* owner) : Component(owner) {}
BodyComponent::~BodyComponent() {}

bool BodyComponent::Initialize(GAME_OBJECTFACTORY_PRESETS& presets)
{
	SpriteComponent* compSprite = _owner->GetComponent<SpriteComponent>();
	GAME_PHYSICS physics;
	if (compSprite != NULL)
	{
		devices = presets.devices;
		physics = devices->GetPhysicsAssetLibrary()->Search(presets.objectType);

		devices->GetPhysicsDevice()->createFixture
			(_owner,
			physics,
			presets);
	}
	oldPosition = presets.position;
	return true;
}

void BodyComponent::Start()
{

}

GameObject* BodyComponent::Update()
{
	GAME_VEC newPosition = devices->GetPhysicsDevice()->GetPosition(_owner);
	dPosition.x = newPosition.x - oldPosition.x;
	dPosition.y = newPosition.y - oldPosition.y;
	oldPosition = newPosition;
	return NULL;
}

void BodyComponent::Finish()
{
	if (!devices->GetPhysicsDevice()->RemoveObject(_owner))
	{
		printf("Object could not be removed from physics world");
		exit(1);
	}
}