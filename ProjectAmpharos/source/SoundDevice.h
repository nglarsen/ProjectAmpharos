///////////////////////////////////////
//Author:	Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		SoundDevice.h
//
//Purpose:	Handles the production of 
//			Sounds
////////////////////////////////////////

#ifndef SOUNDDEVICE_H
#define	SOUNDDEVICE_H

#include "Define.h"
#include <SDL_Mixer.h>


class SoundAssetLibrary;
class SoundDevice 
{
public:
	~SoundDevice();
	bool Initialize();
	void ShutDown();

	bool PlaySound(std::string sound, int numLoops);
	bool PlaySound(std::string sound, int numLoops, int channel);

	void SetBackground(std::string background);
	void SetSoundLibrary(SoundAssetLibrary* sLibrary) { this->sLibrary = sLibrary; }

private:
	SoundAssetLibrary * sLibrary;
};


#endif // !SOUNDDEVICE_H
