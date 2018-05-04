///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		ArtAssetLibrary.h
//
//Purpose:	Store textures for quick
//			object creation
////////////////////////////////////////

#ifndef ARTASSETLIBRARY_H
#define	ARTASSETLIBRARY_H

#include <map>
#include <string>
#include "tinyxml\tinyxml.h"
#include "Texture.h"
#include "GraphicsDevice.h"


class ArtAssetLibrary
{
public:
	ArtAssetLibrary();
	bool Initialize(GraphicsDevice* gDevice);
	Texture* Search(std::string);
	bool AddAsset(std::string name, std::string path);

private:
	std::map < std::string,Texture*> artLibrary;
	GraphicsDevice* gDevice;
};


#endif // !ARTASSETLIBRARY_H
