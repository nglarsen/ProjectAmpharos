
///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		SoundAssetLibrary.h
//
//Purpose:	Store Sounds for quick access
//
////////////////////////////////////////

#ifndef SOUNDASSETLIBRARY_H
#define	SOUNDASSETLIBRARY_H

#include <map>
#include <string>
#include "Define.h"

#include "SoundDevice.h"


class SoundAssetLibrary
{
public:
	SoundAssetLibrary();
	bool Finish();
	bool Initialize(SoundDevice* sDevice);
	Mix_Chunk* SearchSoundEffects(std::string name);
	Mix_Music* SearchMusic(std::string name);
	bool AddSoundEffect(std::string name, std::string path);
	bool AddBackgroundMusic(std::string name, std::string path);
	bool removeAsset(std::string name);

private:
	std::map<std::string, Mix_Chunk*> soundeffectLibrary;
	std::map<std::string, Mix_Music*>	musicLibrary;
	SoundDevice* sDevice;
};


#endif // !SOUNDASSETLIBRARY_H
