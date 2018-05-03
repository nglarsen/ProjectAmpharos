/////////////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		SpriteComponent.h
//
//Purpose:	Handle the sprites of individual
//			units/blocks/background objects
/////////////////////////////////////////////

#ifndef SPRITECOMPONENT_H
#define	SPRITECOMPONENT_H

#include "Component.h"
#include "Define.h"

class Texture;

class SpriteComponent : public Component
{
	SpriteComponent(GameObject*);
	~SpriteComponent();

	bool Initialize(GAME_OBJECTFACTORY_PRESETS& presets);

	void Draw();
	void Draw(GAME_VEC position, GAME_FLT angle);
	void Start();
	GameObject* Update();
	void Finish();

	Texture* GetTexture() { return texture; }
	GAME_VEC GetUpdatedPosition(GameObject*);

	void SetTexture(Texture* texture) { this->texture = texture; }

protected:
	ResourceManager * devices;
	Texture* texture;
	bool initialized;
};



#endif // SPRITECOMPONENT_H
