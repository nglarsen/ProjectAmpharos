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

class Texture
{
public:
	Texture();
	~Texture();

	bool load(SDL_Renderer* renderer, std::string path);
	bool load(SDL_Texture* texture);

	void free();

	void Draw(SDL_Renderer* renderer, GAME_VEC position, GAME_FLT angle, SDL_Rect* clip = NULL);

	int getWidth();
	int getHeight();

private:
	SDL_Texture * texture;

	int height;
	int width;
};



#endif // !TEXTURE_H
