///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		ContactListener.h
//
//Purpose:	Handle collisions for Box2D
//
////////////////////////////////////////

#ifndef CONTACTLISTENER_H
#define	CONTACTLISTENER_H

#include <Box2D.h>
#include "GameObject.h"

class ContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact) {}
	void EndContact(b2Contact* contact){}
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);

	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {}
	void PickUpItem(GameObject* player, GameObject* item);
};



#endif // !CONTACTLISTENER_H
