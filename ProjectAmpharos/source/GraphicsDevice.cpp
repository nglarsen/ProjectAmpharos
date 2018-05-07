///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:			5/2/2018
//
//Header File:	GraphicsDevice.h
//
//Purpose:		
//
////////////////////////////////////////

#include <iostream>
#include "Define.h"
#include "ThirdParty\SDL2_gfx-1.0.1\include\SDL2_gfxPrimitives.h"
#include "ResourceManager.h"
#include "ComponentsList.h"
#include "ObjectFactory.h"
#include "GraphicsDevice.h"
#include "View.h"


GraphicsDevice::GraphicsDevice(GAME_INT width, GAME_INT height) :SCREEN_WIDTH(width), SCREEN_HEIGHT(height)
{
	screen = NULL;
	renderer = NULL;
}	

GraphicsDevice::~GraphicsDevice()
{

}

SDL_Window* GraphicsDevice::GetWindow()
{
	return (screen);
}

bool GraphicsDevice::Initialize(GAME_BOOL fullScreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		PrintError();
		return false;
	}
	if (!IMG_Init(IMG_INIT_PNG))
	{
		printf("SDL_image could not initialize! SDL_Error: %s\n", IMG_GetError());
		return false;
	}
	if (TTF_Init() == -1)
	{
		PrintError();
		return false;
	}
	if (!fullScreen)
	{
		screen = SDL_CreateWindow("Project Ampharos",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, 
				SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	}
	else
	{
		screen = SDL_CreateWindow("Project Ampharos",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	}

	if (screen == NULL)
	{
		PrintError();
		return false;
	}
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		PrintError();
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	//==================
	//Create View
	//==================
	view = new View();
	view->Initialize(0, 0);
	return true;
}


bool GraphicsDevice::ShutDown()
{
	SDL_DestroyWindow(screen);
	screen = NULL;

	//Free Renderer
	SDL_DestroyRenderer(renderer);
	renderer = NULL;

	// Quit SDL Subsystems
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return true;
}

void GraphicsDevice::Begin()
{
	SDL_RenderClear(renderer);
}

void GraphicsDevice::Draw()
{
	for (auto sprite : sprites)
	{
		sprite->Draw();
	}
	////=========================================================
	////===================Draw Overlays=========================
	////=========================================================
	//int cornerRadius = 3;
	//while (!overlays.empty())
	//{
	//	overlay currOverlay = overlays.back();
	//	overlays.pop_back();

	//	//draw the box
	//	roundedBoxRGBA
	//	(
	//		renderer,
	//		currOverlay.topLeft.x,
	//		currOverlay.topLeft.y,
	//		currOverlay.bottomRight.x,
	//		currOverlay.bottomRight.y,
	//		cornerRadius,
	//		currOverlay.boxBackgroundColor.R,
	//		currOverlay.boxBackgroundColor.G,
	//		currOverlay.boxBackgroundColor.B,
	//		currOverlay.boxBackgroundColor.A
	//	);
	//	roundedRectangleRGBA
	//	(
	//		renderer,
	//		currOverlay.topLeft.x,
	//		currOverlay.topLeft.y,
	//		currOverlay.bottomRight.x,
	//		currOverlay.bottomRight.y,
	//		cornerRadius,
	//		currOverlay.boxBackgroundColor.R,
	//		currOverlay.boxBackgroundColor.G,
	//		currOverlay.boxBackgroundColor.B,
	//		currOverlay.boxBackgroundColor.A
	//	);
	//	for (auto object : currOverlay.objects)
	//	{
	//		object.first->Draw(renderer, object.second, 0, NULL);
	//	}


	//}
	//
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);


}

void GraphicsDevice::Present()
{
	SDL_RenderPresent(renderer);
}

SDL_Renderer* GraphicsDevice::GetRenderer()
{
	return(renderer);
}

void GraphicsDevice::AddSpriteRenderer(SpriteComponent* sprite, int x)
{
	sprites.push_back(sprite);
}

void GraphicsDevice::RemoveSpriteRenderer(SpriteComponent* sprite, int x)
{
	std::vector<SpriteComponent*>::iterator spriteIter;
	for (spriteIter = sprites.begin(); spriteIter != sprites.end(); spriteIter++)
	{
		if (*spriteIter == sprite)
		{
			spriteIter = sprites.erase(spriteIter);
		}
	}
}

bool GraphicsDevice::SetFont(std::string path, GAME_INT size, GAME_RGBA color)
{
	font = TTF_OpenFont(path.c_str(), size);
	if(font == NULL)
		{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
			return false;
		}
	this->color = color;
	return(true);
}

void GraphicsDevice::Text2Screen(std::string text, GAME_VEC position)
{
	int widthIncrease = 10;
	int heightIncrease = 2;

	//set color of text
	SDL_Color textColor = { color.R, color.G, color.B, color.A };

	SDL_Texture* textSheetTexture = SDL_CreateTextureFromSurface(renderer,
		TTF_RenderText_Solid(font, text.c_str(), textColor));

	//create a texture for the game.
	Texture* textTexture = new Texture();
	//textTexture->load(textSheetTexture);

	int width = 0, height = 0;

	SDL_QueryTexture(textSheetTexture, NULL, NULL, &width, &height);

	if (position.x == -1)
	{
		position.x = Center(SCREEN_WIDTH, width);
	}

	if (position.y == -1)
	{
		position.y = Center(SCREEN_HEIGHT, height);
	}

	GAME_VEC topLeft = { position.x - widthIncrease, position.y - heightIncrease };
	GAME_VEC bottomRight = { position.x + width + widthIncrease, position.y + height + heightIncrease };

	GAME_RGBA background = { 255,255,255,255 };
	GAME_RGBA border = { 0,0,0,255 };

	std::map<Texture*, GAME_VEC> objects;
	objects[textTexture] = position;

//	DrawOverlay(topLeft, bottomRight, background, border, objects);
}

//adds text to be displayed to the text vector passed on a string and position
//This one lets us directly type the position's values
void GraphicsDevice::Text2Screen(std::string text, GAME_FLT x, GAME_FLT y)
{
	GAME_VEC position = { x,y };
	Text2Screen(text, position);
}

//A notice appears in the inventory bar at the bottom of the screen.
void GraphicsDevice::Notice2Screen(std::string text)
{
	GAME_VEC textVec = { -1,550 };
	Text2Screen(text, textVec);
}

void GraphicsDevice::ReverseOrder()
{
	std::reverse(sprites.begin(), sprites.end());
}

void GraphicsDevice::DrawFilledCircle(GAME_VEC position, GAME_INT radius, GAME_RGBA RGBA)
{
	filledCircleRGBA(renderer, position.x, position.y, radius, RGBA.R, RGBA.G, RGBA.B, RGBA.A);
}

bool GraphicsDevice::DrawBox(GAME_VEC topLeft, GAME_VEC bottomRight, GAME_RGBA RGBA)
{
	boxRGBA(renderer, topLeft.x, topLeft.y, bottomRight.x, bottomRight.y, RGBA.R, RGBA.G, RGBA.B, RGBA.A);
	return true;
}
//
//void GraphicsDevice::DrawOverlay(GAME_VEC topLeft, GAME_VEC bottomRight, GAME_RGBA boxBackgroundColor, GAME_RGBA boxBorderColor, std::map<Texture*, GAME_VEC>objects)
//{
//	overlay newOverlay = { topLeft, bottomRight, boxBackgroundColor, boxBorderColor, objects };
//	overlays.push_back(newOverlay);
//}

GAME_FLT GraphicsDevice::Center(GAME_FLT centerOn, GAME_FLT width)
{
	GAME_FLT point = (centerOn - width) / 2;
	return point;
}