///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:			5/2/2018
//
//Header File:	Texture.h
//
//Purpose:		
//
////////////////////////////////////////

#include "Define.h"
#include "Texture.h"


Texture::Texture()
{
	texture = nullptr;
	height = 0;
	width = 0;
}

Texture::~Texture()
{
	free();
}
bool Texture::load(SDL_Renderer* renderer, std::string path)
{
	//not implemented
}

bool Texture::load(SDL_Texture* texture)
{
	//Not implemented
}

bool Texture::XMLLoad(SDL_Renderer* renderer, TiXmlElement* element)
{
	SDL_Surface* surface = (IMG_Load(element->Attribute("sheet")));
	if (!surface)
	{
		printf("Unable to load Image!\n");
		system("Pause");
	}
	else
	{
		GAME_RGBA RGBA;
		int rgbSet;
		element->QueryIntAttribute("alphaR", &rgbSet);
		RGBA.R = rgbSet;
		element->QueryIntAttribute("alphaG", &rgbSet);
		RGBA.G = rgbSet;
		element->QueryIntAttribute("alphaB", &rgbSet);
		RGBA.B = rgbSet;

		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, RGBA.R, RGBA.G, RGBA.B));
		element->QueryStringAttribute("name", &this->name);
		texture = (SDL_CreateTextureFromSurface(renderer, surface));
		if (!texture)
		{
			printf("Unable to create texture from image!\n");
			system("Pause");
		}
		else
		{
			element->QueryIntAttribute("width", &width);
			element->QueryIntAttribute("height", &height);

			//Okay so let's break down clip the double SDL_Rect Pointer
			//clip is used to load the animation states for SDL_RenderCopyEx
			//Clip[i][j] where i is the state # and j is the animation #
			//State is like running jumping etc
			//Animation # is the series of xy values after it

			
			element->QueryIntAttribute("numStates", &numStates);
			//Now we can loop through and set the rectangle's top left corners up
			//Reminder: This is not where we animate, this is preparing animation
			clip = new SDL_Rect*[numStates];
			TiXmlElement* xmlState = element->FirstChildElement("State");

			
			xmlState->QueryIntAttribute("numClips", &numClips);

			TiXmlElement* xmlClip = xmlState->FirstChildElement("Clip");

			for (int i = 0; i < numStates; i++)
			{
				clip[i] = new SDL_Rect[numClips];
				for (int j = 0; j < numClips; j++)
				{
					xmlClip->QueryIntAttribute("x", &clip[i][j].x);
					xmlClip->QueryIntAttribute("y", &clip[i][j].y);
					clip[i][j].h = height;
					clip[i][j].w = width;
				}
			}
		}
	}
	if (texture)
	{
		return true;
	}
	else
	{
		return false;
	}

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

void Texture::Draw(SDL_Renderer * renderer, GAME_VEC position, GAME_FLT angle, SDL_Rect * clip)
{
	//Need to handle animation here but not positive how
	//Sprite Component maybe keeps up with State and Clip via Update()
	SDL_RenderCopyEx(renderer, texture, &this->clip[0][0], clip, angle, NULL, SDL_FLIP_NONE);

}
