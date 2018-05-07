///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:			5/2/2018
//
//Header File:	ContactListener.h
//
//Purpose:		Handle Collision for 
//				Box2D
////////////////////////////////////////

#include "Define.h"
#include "ContactListener.h"

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	// Grab the two physics bodies involved
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	//Cast to Object *
	GameObject* objectA = static_cast<GameObject*>(bodyA->GetUserData());
	GameObject* objectB = static_cast<GameObject*>(bodyB->GetUserData());

	std::string objectAType = objectA->getObjectType();
	std::string objectBType = objectB->getObjectType();

	if (objectAType == "Player")
	{
		//if we found a pickup item, grab it
		if (objectB->GetComponent<PowerUpComponent>())
		{
			PickUpItem(objectA, objectB);
		}
		if (objectBType == "Goomba")
		{
			if(objectA->GetComponent<SpriteComponent>()->getEvoState()>0)
			objectA->GetComponent<SpriteComponent>()->setEvoState(objectA->GetComponent<SpriteComponent>()->getEvoState() - 1);
		}
	}
}

void ContactListener::PickUpItem(GameObject* player, GameObject* item)
{
	ResourceManager* devices = player->GetComponent<BodyComponent>()->GetDevices();

	if (player->GetComponent<SpriteComponent>()->getEvoState() < 2)
	{
		player->GetComponent<SpriteComponent>()->setEvoState((int)player->GetComponent<SpriteComponent>()->getEvoState() + 1);
		devices->GetSoundDevice()->PlaySound("found", 0, 3);
	}
}