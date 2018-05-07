///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:			5/2/2018
//
//Header File:	View.h
//
//Purpose:		Handle the movement
//				for positioning camera
////////////////////////////////////////

#include "Define.h"
#include "View.h"
View::View()
{

}

View::~View()
{

}

bool View::Initialize(GAME_FLT x, GAME_FLT y)
{
	position.x = x;
	position.y = y;
	return true;
}


//not used
bool View::Update(GAME_FLT gameTime)
{
	return true;
}

void View::Print()
{
	printf("**********VIEW*************\nView X: %d\nView Y: %d\n", position.x, position.y);
}
