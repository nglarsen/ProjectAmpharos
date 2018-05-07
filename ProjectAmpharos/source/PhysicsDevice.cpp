///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:			5/2/2018
//
//Header File:	PhysicsDevice.cpp
//
//Purpose:		
//
////////////////////////////////////////

#include "Define.h"
#include "PhysicsDevice.h"
#include "ContactListener.h"

PhysicsDevice::PhysicsDevice(GAME_FLT gravityX, GAME_FLT gravityY) :gravity(RW2PW(gravityX), RW2PW(gravityY))
{
}

bool PhysicsDevice::Initialize()
{
	world = new b2World(gravity);
	if (world == NULL) return false;
	ContactListener* c1 = new ContactListener();
	world->SetContactListener(c1);
	return true;
}

bool PhysicsDevice::Update(float dt)
{
	world->Step(dt, 8, 3);
	return true;
}

bool PhysicsDevice::SetTransform(GameObject* object, GAME_VEC position, GAME_FLT angle)
{
	//finds which body this object is attached to.
	//based on value set in UserData field of body
	b2Body* body = FindBody(object);

	body->SetTransform
	(
		GV2PV(position),
		RW2PWAngle(angle)
	);
	return true;
}

bool PhysicsDevice::SetAngle(GameObject* object, GAME_FLT angle)
{
	b2Body* body = FindBody(object);
	body->SetTransform(body->GetPosition(), RW2PWAngle(angle));
	return true;
}

bool PhysicsDevice::SetAngularVelocity(GameObject* object, GAME_FLT angularVelocity)
{
	b2Body* body = FindBody(object);
	body->SetAngularVelocity(RW2PW(angularVelocity));
	return true;
}

bool PhysicsDevice::SetLinearVelocity(GameObject* object, GAME_VEC linearVelocity)
{
	b2Body* body = FindBody(object);
	b2Vec2 b2LVelocity;
	b2LVelocity.x = RW2PW(linearVelocity.x);
	b2LVelocity.y = RW2PW(linearVelocity.y);
	body->SetLinearVelocity(b2LVelocity);
	return true;

}

bool PhysicsDevice::SetLinearImpulse(GameObject* object, GAME_VEC forceVec, GAME_VEC forceCenter)
{
	b2Body* body = FindBody(object);
	body->ApplyLinearImpulse
	(
		GV2PV(forceVec),
		body->GetWorldPoint(GV2PV(forceCenter)),
		true
	);
	return true;
}

bool PhysicsDevice::SetTorque(GameObject* object, GAME_FLT torque)
{
	b2Body* body = FindBody(object);
	body->ApplyTorque(RW2PW(torque), true);
	return true;
}

bool PhysicsDevice::SetStatic(GameObject* object)
{
	b2Body* body = FindBody(object);
	body->SetType(b2_staticBody);
	return true;
}

bool PhysicsDevice::SetStopPhysics(GameObject* object)
{
	b2Body* body = FindBody(object);
	body->SetActive(false);
	return true;
}

GAME_FLT PhysicsDevice::GetAngularVelocity(GameObject* object)
{
	b2Body* body = FindBody(object);
	return (PW2RWAngle(body->GetAngularVelocity()));
}

GAME_VEC PhysicsDevice::GetLinearVelocity(GameObject* object)
{
	b2Body* body = FindBody(object);
	return(PV2GV(body->GetLinearVelocity()));
}

GAME_VEC PhysicsDevice::GetPosition(GameObject* object)
{
	return (AlignCenters(object));
}

GAME_FLT PhysicsDevice::GetAngle(GameObject* object)
{
	b2Body* body = FindBody(object);
	return (PW2RWAngle(body->GetAngle()));
}

GAME_VEC PhysicsDevice::GetVelocity(GameObject* object)
{
	b2Body* body = FindBody(object);
	return(PV2GV(body->GetLinearVelocity()));
}

bool PhysicsDevice::createFixture
(
	GameObject* object,
	GAME_PHYSICS physics,
	GAME_OBJECTFACTORY_PRESETS presets
)
{
	SpriteComponent* spriteComp = object->GetComponent<SpriteComponent>();

	b2BodyDef* bd = new b2BodyDef;

	b2PolygonShape pShape;
	b2CircleShape cShape;

	b2FixtureDef shapefd;

	bd->userData = object;

	switch (physics.bodyType)
	{
	case GAME_STATIC:
		bd->type = b2_staticBody;
		break;
	case GAME_KINEMATIC:
		bd->type = b2_kinematicBody;
		break;
	case GAME_DYNAMIC:
		bd->type = b2_dynamicBody;
		break;
	}

	Texture* texture = object->GetComponent<SpriteComponent>()->GetTexture();

	presets.position.x += (texture->getWidth() / 2);
	presets.position.y += (texture->getHeight() / 2);

	bd->position.Set(RW2PW(presets.position.x), RW2PW(presets.position.y));

	bd->angle = RW2PWAngle(presets.angle);

	b2Body* body = world->CreateBody(bd);

	body->SetAngularDamping(physics.angularDamping);
	body->SetLinearDamping(physics.linearDamping);

	//set fixture's shape
	switch (physics.bodyShape)
	{
	case GAME_RECTANGLE:
		pShape.SetAsBox(RW2PW(spriteComp->GetTexture()->getWidth() / 2.0f), RW2PW(spriteComp->GetTexture()->getHeight() / 2.0f));
		shapefd.shape = &pShape;
		break;
	case GAME_CIRCLE:
		GAME_FLT width = spriteComp->GetTexture()->getWidth() / 2.0f;
		GAME_FLT height = spriteComp->GetTexture()->getHeight() / 2.0f;

		if (width > height) cShape.m_radius = (RW2PW(width));
		else cShape.m_radius = (RW2PW(height));
		shapefd.shape = &cShape;
		break;
	}

	//set fixture values based on passed in values.

	shapefd.density = physics.density;
	shapefd.friction = physics.friction;
	shapefd.restitution = physics.restitution;

	//create the fixture on the body.
	body->CreateFixture(&shapefd);
	body->SetActive(physics.physicsOn);
	return true;
}

bool PhysicsDevice::RemoveObject(GameObject* object)
{
	//Find body
	b2Body* body = FindBody(object);
	DestroyJoint(body);

	if (body == NULL)
	{
		return false;
	}
	else
	{
		world->DestroyBody(body);
		return true;
	}
}

bool PhysicsDevice::DestroyJoint(GameObject* object)
{
	b2Body* body = FindBody(object);

	return DestroyJoint(body);
}

bool PhysicsDevice::DestroyJoint(b2Body* body)
{
	bool jointFound = false;

	for (b2JointEdge* j = body->GetJointList(); j != NULL; j = j->next)
	{
		world->DestroyJoint(j->joint);
		jointFound = true;
	}
	return jointFound;
}

b2Body* PhysicsDevice::FindBody(GameObject* object)
{
	for (b2Body* body = world->GetBodyList(); body; body = body->GetNext())
	{
		//when we match return it
		if (object == body->GetUserData())
		{
			return body;
		}
	}
	return NULL;
}

b2Vec2 PhysicsDevice::GV2PV(GAME_VEC gameVec)
{
	return b2Vec2(RW2PW(gameVec.x), RW2PW(gameVec.y));
}

GAME_VEC PhysicsDevice::PV2GV(b2Vec2 physicsVec)
{
	GAME_VEC temp;
	temp.x = PW2RW(physicsVec.x);
	temp.y = PW2RW(physicsVec.y);
	return temp;
}

bool PhysicsDevice::CreateRevolvingJoint(GameObject* object1, GameObject* object2, GAME_VEC anchor1, GAME_VEC anchor2)
{
	//find corresponding bodies for objects
	b2Body* bodyA = FindBody(object1);
	b2Body* bodyB = FindBody(object2);

	if (bodyA == NULL || bodyB == NULL)
	{
		return false;
	}

	//joint definition
	b2RevoluteJointDef revoluteJointDef;

	//assign bodies to definition
	revoluteJointDef.bodyA = bodyA;
	revoluteJointDef.bodyB = bodyB;

	revoluteJointDef.collideConnected = false;

	//set anchors
	revoluteJointDef.localAnchorA.Set(RW2PW(anchor1.x), RW2PW(anchor1.y));
	revoluteJointDef.localAnchorB.Set(RW2PW(anchor2.x), RW2PW(anchor2.y));

	//Joint starts at angle 0

	revoluteJointDef.referenceAngle = 0;

	return (b2RevoluteJoint*)world->CreateJoint(&revoluteJointDef);

}

GAME_VEC PhysicsDevice::AlignCenters(GameObject* object)
{
	b2Body* body = FindBody(object);
	b2Vec2 physPosition = body->GetPosition();
	GAME_VEC position;
	Texture* texture = object->GetComponent<SpriteComponent>()->GetTexture();

	position.x = PW2RW(physPosition.x) - (texture->getWidth() / 2);
	position.y = PW2RW(physPosition.y) - (texture->getHeight() / 2);

	return position;
}