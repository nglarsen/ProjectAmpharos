///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:			5/2/2018
//
//Header File:	SoundDevice.h
//
//Purpose:		Handle Sound production
//
////////////////////////////////////////

#include "Define.h"
#include "SoundDevice.h"
#include "SoundAssetLibrary.h"

SoundDevice::~SoundDevice()
{
	ShutDown();
}

bool SoundDevice::Initialize()
{
	int flags = MIX_INIT_OGG;
	int initted = Mix_Init(flags);

	if (initted&flags != flags)
	{
		printf("Mix_init: failed to init ogg\n");
		printf("mix_init:%s\n", Mix_GetError());
	}
	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		printf("SDL MIXER COULDN'T INIT %s\n", Mix_GetError());
		exit(1);
	}

	int numChannels = 100;
	Mix_AllocateChannels(numChannels);
}

bool SoundDevice::PlaySound(std::string sound, int numLoops)
{
	int channelID = -1; // select first channel available
	PlaySound(sound, numLoops, channelID);
	return true;
}

bool SoundDevice::PlaySound(std::string sound, int numLoops, int channel)
{
	Mix_PlayChannel(channel, sLibrary->SearchSoundEffects(sound), numLoops);
	return true;
}

void SoundDevice::SetBackground(std::string background)
{
	if (Mix_PlayMusic(sLibrary->SearchMusic(background), -1) == -1)
	{
		printf("Mix_PlayMusic: %s\n", Mix_GetError());
	}
}

void SoundDevice::ShutDown()
{

}
