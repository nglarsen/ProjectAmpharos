///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:			5/2/2018
//
//Header File:	Texture.h
//
//Purpose:		Store Textures and
//				Load them for sprites
////////////////////////////////////////

#include "Define.h"
#include "Texture.h"

Texture::Texture()
{
	width = 0;
	height = 0;
	texture = NULL;
}
Texture::~Texture()
{
	free();
}

bool Texture::load(SDL_Renderer* renderer, std::string path)
{
	//Destroy Existing texture information
	free();

	//The image that's loaded
	SDL_Surface* surface = NULL;

	surface = IMG_Load(path.c_str());

	if (surface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color Key image
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 0, 255));

		texture = SDL_CreateTextureFromSurface(renderer, surface);

		if (texture == NULL)
		{
			printf("unable to create texture from image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			SDL_QueryTexture(texture, NULL, NULL, &width, &height);
			SDL_FreeSurface(surface);
		}
	}
	return(texture != NULL);
}

bool Texture::load(SDL_Texture* texture)
{
	this->texture = texture;
	//Set Height and width from the texture
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	return true;
}

void Texture::free()
{
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

void Texture::Draw(SDL_Renderer* renderer, GAME_VEC position, GAME_FLT angle, SDL_Rect* clip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { position.x,position.y,width,height };

	//Set Clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, NULL, SDL_FLIP_NONE);

}

int Texture::getHeight() { return height; }
int Texture::getWidth() { return width; }
