#include "PowerUpComponent.h"
#include "SpriteComponent.h"


PowerUpComponent::PowerUpComponent(GameObject* owner) :Component(owner) {}

PowerUpComponent::~PowerUpComponent()
{

}

bool PowerUpComponent::Initialize(GAME_OBJECTFACTORY_PRESETS& presets)
{
	return true;
}

void PowerUpComponent::Start()
{

}


GameObject* PowerUpComponent::Update()
{
	return _owner;
}
void PowerUpComponent::Finish()
{

}

