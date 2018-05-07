///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:			5/2/2018
//
//Header File:	SpriteComponent.h
//
//Purpose:		Handle drawing sprites
//
////////////////////////////////////////

#include "Define.h"
#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(GameObject* owner) :Component(owner) { initialized = false; }
SpriteComponent::~SpriteComponent() {}

bool SpriteComponent::Initialize(GAME_OBJECTFACTORY_PRESETS& presets)
{
	if (initialized == false)
	{
		devices = presets.devices;
		//Set this as the renderer for this object
		devices->GetGraphicsDevice()->AddSpriteRenderer(this,NULL);

		//grab the sprite from the library
		texture = presets.devices->GetArtAssetLibrary()->Search(presets.objectType);
		initialized = true;
	}
	return true;
}

void SpriteComponent::Draw()
{
	GAME_VEC updatedPosition;

	updatedPosition = GetUpdatedPosition(_owner);
	GAME_FLT angle = devices->GetPhysicsDevice()->GetAngle(_owner);

	Draw(updatedPosition, angle);


}

void SpriteComponent::Draw(GAME_VEC position, GAME_FLT angle)
{
	
	texture->Draw(devices->GetGraphicsDevice()->GetRenderer(), position, angle, NULL);
}

void SpriteComponent::Start()
{

}

GameObject* SpriteComponent::Update() { return NULL; }

GAME_VEC SpriteComponent::GetUpdatedPosition(GameObject* owner)
{
	GAME_VEC updatedPosition;
	GAME_VEC position = devices->GetPhysicsDevice()->GetPosition(owner);
	updatedPosition.x =
		position.x + devices->GetGraphicsDevice()->GetView()->getPosition().x;

	updatedPosition.y =
		position.y + devices->GetGraphicsDevice()->GetView()->getPosition().y;

	return updatedPosition;
}

void SpriteComponent::Finish()
{
	devices->GetGraphicsDevice()->RemoveSpriteRenderer(this,NULL);
}