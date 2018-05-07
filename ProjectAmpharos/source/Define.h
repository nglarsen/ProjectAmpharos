//////////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		Define.h
//
//Purpose:	Centralized location to pass
//			pointers and hold constants
//
//Reference: Definitions.h from MightyMage
///////////////////////////////////////////
#ifndef DEFINE_H
#define DEFINE_H

#include <string>
#include <map>
#include <memory>

//Forward Declarations
class ResourceManager; //Love this idea Mr. Orme, totally stealing it for my rebuild.


typedef unsigned int Uint32;
typedef float GAME_FLT;
typedef Uint32 GAME_INT;
typedef bool GAME_BOOL;

enum GAME_OBJECT_SHAPE { GAME_RECTANGLE, GAME_CIRCLE };
enum GAME_BODY_TYPE { GAME_STATIC, GAME_KINEMATIC, GAME_DYNAMIC };

//Event Types
enum GAME_EVENT {GAME_NA, GAME_UP, GAME_DOWN, GAME_LEFT, GAME_RIGHT, GAME_SPACE, GAME_QUIT, GAME_SHIFT, GAME_NUM_EVENTS};
enum GAME_DIRECTION {UP = GAME_UP, DOWN=GAME_DOWN, LEFT=GAME_LEFT, RIGHT=GAME_RIGHT};

//Evolutions
enum POWERUP_LEVELS{MAREEP, FLAFFLE, AMPHAROS};



enum GAME_COMPONENT_LIST
{
	GAME_BODY_COMP,
	//GAME_HEALTH_COMP, Maybe, unsure because using SMW rules
	GAME_SPRITE_COMP,
	GAME_CONTROL_COMP,
	GAME_POWERUP_COMP,
	GAME_ITEMBLOCK_COMP
};

typedef struct GAME_VEC
{
	GAME_FLT x;
	GAME_FLT y;
} GAME_VEC;

typedef struct GAME_ROTATE_STRUCT
{
	GAME_FLT torque;
	GAME_FLT maxAngularVelocity;
	GAME_INT radius;
	GAME_VEC center;
} GAME_ROTATE_STRUCT;

typedef struct GAME_PHYSICS
{
	GAME_FLT spinSpeed;
	GAME_BODY_TYPE bodyType;
	GAME_OBJECT_SHAPE bodyShape;
	GAME_FLT density;
	GAME_FLT friction;
	GAME_FLT restitution;
	GAME_FLT angularDamping;
	GAME_FLT linearDamping;
	GAME_FLT force;
	GAME_BOOL physicsOn;
} GAME_PHYSICS;

typedef struct GAME_OBJECTFACTORY_PRESETS
{
	std::string objectType;
	GAME_VEC position;
	GAME_FLT angle;
	ResourceManager* devices;
	std::map<GAME_DIRECTION, bool> gDirection;
}GAME_OBJECTFACTORY_PRESETS;

typedef struct GAME_OBJECT_STATS
{
	int health;
}GAME_OBJECT_STATS;

typedef struct GAME_RGBA
{
	GAME_INT R;
	GAME_INT G;
	GAME_INT B;
	GAME_INT A;
}GAME_RGBA; //Included from Mr. Orme's Definitions.h but unsure if I'll use it, maybe for the spritesheet Alpha?

typedef struct GAME_NOTICE
{
	GAME_INT x;
	GAME_INT y;
	GAME_DIRECTION direction; //Probably not what I want for my use, potentially will change this entire struct but it's a start
	std::string text;
}GAME_NOTICE;




//Constants
const GAME_FLT PI = 3.14159f;
const float fPRV = 10.0f;
#endif // !DEFINE_H
