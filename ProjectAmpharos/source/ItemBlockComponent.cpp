///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:			5/2/2018
//
//Header File:	ItemBlockComponent.h
//
//Purpose:		Store powerup
//
////////////////////////////////////////

#include "Define.h"
#include "ItemBlockComponent.h"
#include "GameObject.h"


//Init open to false
ItemBlockComponent::ItemBlockComponent(GameObject* owner) : Component(owner)
{
	open = false;
	looted = false;
}
ItemBlockComponent::~ItemBlockComponent()
{

}

//Swap texture and spawn powerup above block
void ItemBlockComponent::spawnPowerUp()
{
	SpriteComponent* sprite = _owner->GetComponent<SpriteComponent>();
	Texture* texture = artLibrary->Search("openItemBlock");
	sprite->SetTexture(texture);
}


bool ItemBlockComponent::Initialize(GAME_OBJECTFACTORY_PRESETS& presets)
{
	artLibrary = presets.devices->GetArtAssetLibrary();
	this->presets = presets;
	return true;
}
void ItemBlockComponent::Start()
{
	//
}

//check open and looted, if both true call finish and delete
GameObject* ItemBlockComponent::Update()
{
	_owner->GetComponent<SpriteComponent>()->setEvoState(_owner->GetComponent<SpriteComponent>()->getEvoState() + 1);
	return _owner;
}

//When powerup is picked up delete the block
void ItemBlockComponent::Finish()
{

}