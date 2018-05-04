///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		Texture.h
//
//Purpose:	handles the drawing and 
//			animation of textures
////////////////////////////////////////

#ifndef TEXTURE_H
#define	TEXTURE_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Define.h"
#include "tinyxml\tinyxml.h"

class Texture
{
public:
	Texture();
	~Texture();

	bool load(SDL_Renderer* renderer, std::string path);
	bool load(SDL_Texture* texture);
	bool XMLLoad(SDL_Renderer* renderer, TiXmlElement* element);
	void free();

	void Draw(SDL_Renderer* renderer, GAME_VEC position, GAME_FLT angle, SDL_Rect* clip = NULL);

	int getWidth() { return width; }
	int getHeight() { return height; }
	int getNumStates() { return numStates; }
	int getNumClips() { return numClips; }
	SDL_Rect** getClip() { return clip; }
	std::string getName() { return name; }

private:
	SDL_Texture * texture;
	SDL_Rect** clip;
	int height;
	int width;
	int numClips;
	int numStates;
	int animationState;
	

	std::string name;
};



#endif // !TEXTURE_H
