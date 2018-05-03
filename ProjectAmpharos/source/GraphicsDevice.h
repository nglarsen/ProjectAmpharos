///////////////////////////////////////
//Author:	Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		GraphicsDevice.h
//
//Purpose:	Handle Rendering of sprites
//			
////////////////////////////////////////

#ifndef GRAPHICSDEVICE_H
#define	GRAPHICSDEVICE_H

#include <vector>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "SpriteComponent.h"

#include "Define.h"

class View;

class GraphicsDevice
{
public:
	//Constructor takes in X and Y position of View
	GraphicsDevice(GAME_INT, GAME_INT);
	~GraphicsDevice();

	//Startup and Shutdown
	bool Initialize(GAME_BOOL);
	bool ShutDown();

	//Rendering Functions
	void Begin();
	void Draw();
	void Present();

	void Text2Screen(std::string text, GAME_VEC position);
	void Text2Screen(std::string text, GAME_FLT x, GAME_FLT y);
	void Notice2Screen(std::string text);
	void Menu2Screen(std::vector<std::string>);

	void DrawFilledCircle(GAME_VEC position, GAME_INT radius, GAME_RGBA RGBA);
	bool DrawBox(GAME_VEC topLeft, GAME_VEC bottomRight, GAME_RGBA RGBA);

	void DrawOverlay
	(
		//DEV NOTE: Thanks for this, I think this is what I was looking for with Menu2Screen
		//round corner box that contains overlay
		GAME_VEC topLeft, GAME_VEC bottomRight, GAME_RGBA boxBackgroundColor, GAME_RGBA boxBorderColor,
		//Any objects drawn in the stated box at given position
		std::map<Texture*, GAME_VEC> objects
	);

	void ReverseOrder();

	//Curious about this one
	GameObject* GetExit() { return levelExit; }

	//Accessors
	void AddSpriteRenderer(SpriteComponent*);
	void RemoveSpriteRenderer(SpriteComponent*);

	//Getters
	SDL_Renderer* GetRenderer();
	SDL_Window* GetWindow();
	GAME_INT GetScreenHeight() { return SCREEN_HEIGHT; }
	GAME_INT GetScreenWidth() { return SCREEN_WIDTH; }
	View* GetView() { return view; }

	//Setters
	void SetView(View* view) { this->view = view;}
	void SetExit(GameObject* levelExit) { this->levelExit = levelExit; }
	bool SetFont(std::string path, GAME_INT size, GAME_RGBA color);

private:
	GAME_FLT Center(GAME_FLT centerOn, GAME_FLT width);
	//Parameters
	const Uint32 SCREEN_WIDTH;
	const Uint32 SCREEN_HEIGHT;

	SDL_Window* screen;
	SDL_Renderer* renderer;

	//Sprites
	std::vector<SpriteComponent*> sprites;
	View* view;

	typedef struct overlay
	{
		GAME_VEC topLeft;
		GAME_VEC bottomRight;
		GAME_RGBA boxBackgroundColor;
		GAME_RGBA boxBorderColor;
		std::map<Texture*, GAME_VEC> objects;
	}overlay;

	std::vector<overlay> overlays;

	TTF_Font* font;
	GAME_RGBA color;

	GameObject* levelExit;
};



#endif // GRAPHICSDEVICE_H
