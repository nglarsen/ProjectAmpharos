///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:			5/2/2018
//
//Header File:	ControllerComponent.h
//
//Purpose:		
//
////////////////////////////////////////

#include "Define.h"
#include "ControllerComponent.h"
#include "ComponentsList.h"
#include "GameObject.h"

ControllerComponent::ControllerComponent(GameObject* owner) : Component(owner){}
ControllerComponent::~ControllerComponent() {}

bool ControllerComponent::Initialize(GAME_OBJECTFACTORY_PRESETS& presets)
{
	frameCount=0;
	zeroVec.x = 0;
	zeroVec.y = 0;
	devices = presets.devices;

	wallHit = false;
	noWall = true;

	for (int i = 0; i < GAME_NUM_EVENTS; i++)
	{
		GAME_EVENT eventNum = static_cast<GAME_EVENT>(i);
		pressControl[eventNum] = true;
	}

	return true;
}

void ControllerComponent::Start(){}

GameObject* ControllerComponent::Update()
{
	frameCount++;
	bool locationMarker = false;
	GAME_VEC applyForce;
	GAME_INT baseForceMultiplier = 1500; //Base speed
	GAME_INT forceMultiplier = baseForceMultiplier;
	GAME_INT runMultiplier = 3;
	GAME_INT angleAdjust = 90;
	GAME_INT soundWait = devices->GetGAME_FPS() / 5;

	std::string sound = "walking";

	if (devices->GetControllerDevice()->GetEvent(GAME_SHIFT))
	{
		//Run with shift
		forceMultiplier = baseForceMultiplier * runMultiplier;
		//play sound faster
		soundWait = devices->GetGAME_FPS() / 8;
		//do the run sound gud
		sound = "run";
	}
	else
	{
		forceMultiplier = baseForceMultiplier;
	}

	bool playWalk = false;
	if (frameCount > soundWait + 1)
	{
		frameCount = soundWait + 1;
		playWalk = true;
	}

	GAME_VEC velocity = devices->GetPhysicsDevice()->GetVelocity(_owner);

	if (devices->GetControllerDevice()->GetEvent(GAME_UP))
	{
		//Calculate the force vector for a forward push
		applyForce.x = (float)cosf((devices->GetPhysicsDevice()->GetAngle(_owner)*PI / 180) - (PI / 2))*forceMultiplier;
		applyForce.y = (float)cosf((devices->GetPhysicsDevice()->GetAngle(_owner)*PI / 180) - (PI / 2))*forceMultiplier;

		devices->GetPhysicsDevice()->SetLinearVelocity(_owner, applyForce);
		if (playWalk == true && (abs(velocity.x) > 1 || abs(velocity.y) > 1))
		{
			devices->GetSoundDevice()->PlaySound(sound, 0, 1);
			frameCount = 0;
		}

		if (!noWall && wallHit && abs(velocity.x) < 1 && abs(velocity.y) < 1)
		{
			devices->GetSoundDevice()->PlaySound("wall", 0, 2);

		}
		noWall = false;
	}
	else if (devices->GetControllerDevice()->GetEvent(GAME_DOWN))
	{
		//Force reversed from the UP force by adding PI to the angle.
		applyForce.x = (float)cosf((devices->GetPhysicsDevice()->GetAngle(_owner)*PI / 180) + (PI / 2))*forceMultiplier;
		applyForce.y = (float)cosf((devices->GetPhysicsDevice()->GetAngle(_owner)*PI / 180) + (PI / 2))*forceMultiplier;

		//PUSH BABY PUSH!!!
		devices->GetPhysicsDevice()->SetLinearVelocity(_owner, applyForce);
		//if last play is done and still moving
		if (playWalk == true && (abs(velocity.x) > 1 || abs(velocity.y) > 1))
		{
			//play walking sound
			devices->GetSoundDevice()->PlaySound(sound, 0, 1);

			frameCount = 0;
		}
		//same as up arrow....
		if (!noWall && wallHit && abs(velocity.x) < 1 && abs(velocity.y) < 1)
		{
			devices->GetSoundDevice()->PlaySound("wall", 0, 2);
		}
		noWall = false;


	}
	//if neither are pressed, remove velocity
	else
	{
		devices->GetPhysicsDevice()->SetLinearVelocity(_owner, zeroVec);
		//make sure we won't make a wall sound the first frame after we press an up or down arrow.
		noWall = true;
	}

	//Check for left or right buttons
	//the turn variable makes sure we only turn once every time we push the button

	if (devices->GetControllerDevice()->GetEvent(GAME_RIGHT))
	{
		if (pressControl[GAME_RIGHT])
		{
			//set angle by angle adjust
			devices->GetPhysicsDevice()->SetAngle(
				_owner,
				devices->GetPhysicsDevice()->GetAngle(_owner) + angleAdjust);
			//stop forward motion
			devices->GetPhysicsDevice()->SetLinearVelocity(_owner, zeroVec);
			//ensures we only turn once per press
			pressControl[GAME_RIGHT] = false;

		}
		noWall = true;
	}
	else pressControl[GAME_RIGHT] = true;
	if (devices->GetControllerDevice()->GetEvent(GAME_LEFT))
	{
		if (pressControl[GAME_LEFT])
		{
			//set angle by angle adjust
			devices->GetPhysicsDevice()->SetAngle(
				_owner,
				devices->GetPhysicsDevice()->GetAngle(_owner) - angleAdjust);
			//stop forward motion
			devices->GetPhysicsDevice()->SetLinearVelocity(_owner, zeroVec);
			//ensures we only turn once per press
			pressControl[GAME_LEFT] = false;

		}
		noWall = true;
	}
	else pressControl[GAME_LEFT] = true;
/*	Menu Open
	if (devices->GetInputDevice()->GetEvent(GAME_B))
	{
		if (pressControl[GAME_B])
		{
			std::shared_ptr<BackpackComponent> backpack = _owner->GetComponent<BackpackComponent>();
			if (backpack != NULL)
			{
				if (backpack->GetOpen()) backpack->SetOpen(false);
				else backpack->SetOpen(true);
			}
			pressControl[GAME_B] = false;
		}

	}
	else pressControl[GAME_B] = true;*/
		
	//True to 90
	//Sometimes the angle gets off perpendicular

	int angle = (int(devices->GetPhysicsDevice()->GetAngle(_owner)));

	if (angle > 360 && angle < 460) angle = 90;
	if (angle < 0) angle = 270;
	if (angle < 45 && angle >= 315) devices->GetPhysicsDevice()->SetAngle(_owner,0);
	else if (angle < 135 && angle >= 45) devices->GetPhysicsDevice()->SetAngle(_owner, 90);
	else if (angle < 225&& angle >= 135) devices->GetPhysicsDevice()->SetAngle(_owner, 180);
	else if (angle < 315 && angle >= 225) devices->GetPhysicsDevice()->SetAngle(_owner, 270);

	//BORDER Detection

	//Distance from the edge of the screen before the screen updates.
	GAME_INT border = 200;

	//The amount the screen moves is based on the last change in position for the player.
	GAME_VEC jump = _owner->GetComponent<BodyComponent>()->GetDPosition();

	//Grab a few things we'll need
	PhysicsDevice* pDevice = devices->GetPhysicsDevice();
	GraphicsDevice* gDevice = devices->GetGraphicsDevice();

	View* view = devices->GetGraphicsDevice()->GetView();

	//position plus view
	GAME_VEC position = _owner->GetComponent<SpriteComponent>()->GetUpdatedPosition(_owner);

	//Check distance for each border and adjust view if too close.
	//It is always - jump because Dposition's sign changes based on the direction of movement
	//left
	if (position.x < border)
	{
		view->setX(view->getPosition().x - jump.x);
	}
	//right
	else if (position.x > gDevice->GetScreenWidth() - border)
	{
		view->setX(view->getPosition().x - jump.x);
	}
	if (position.y < border)
	{
		view->setY(view->getPosition().y - jump.y);
	}
	else if (position.y > gDevice->GetScreenHeight() - border)
	{
		view->setY(view->getPosition().y - jump.y);
	}
	return _owner;
}

GAME_VEC ControllerComponent::GetCurrentSquare()
{
	////View playerr's position
	//GAME_VEC playerPosition;
	//playerPosition.x = _owner->GetComponent<SpriteComponent>()->GetUpdatedPosition(_owner).x;
	//playerPosition.y = _owner->GetComponent<SpriteComponent>()->GetUpdatedPosition(_owner).y;

	////view vector
	//GAME_VEC viewPosition;
	//viewPosition.x = devices->GetGraphicsDevice()->GetView()->getPosition().x;
	//viewPosition.y = devices->GetGraphicsDevice()->GetView()->getPosition().y;

	////The coords of the original top left city corner.
	//GAME_VEC cityCorner;
	//cityCorner.x = devices->GetCityCorner().x;

	//
	GAME_VEC tempVec = { NULL, NULL };
	return tempVec;
}

void ControllerComponent::Finish()
{
}
