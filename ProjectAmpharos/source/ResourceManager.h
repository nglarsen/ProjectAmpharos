///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:		5/2/2018
//
//File:		ResourceManager.h
//
//Purpose:	A class to control all 
//			devices and libraries
////////////////////////////////////////

#ifndef RESOURCEMANAGER_H
#define	RESOURCEMANAGER_H

#include "GraphicsDevice.h"
#include "ControllerDevice.h"
#include "PhysicsDevice.h"
#include "SoundDevice.h"
#include "ArtAssetLibrary.h"
#include "PhysicsAssetLibrary.h"
#include "ComponentAssetLibrary.h"
#include "ObjectAssetLibrary.h"
#include "SoundAssetLibrary.h"
#include "View.h"

#include "Define.h"



class ObjectFactory;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	bool Initialize(GAME_INT SCREEN_WIDTH, GAME_INT SCREEN_HEIGHT, std::string assetPath);
	bool ShutDown();
	
	//Device Getters
	GraphicsDevice* GetGraphicsDevice() { return gDevice; }
	ControllerDevice* GetControllerDevice() { return cDevice; }
	PhysicsDevice* GetPhysicsDevice() { return physicsDevice; }
	SoundDevice* GetSoundDevice() { return sDevice; }
	
	//Library Getters
	ArtAssetLibrary* GetArtAssetLibrary() { return artLibrary; }
	PhysicsAssetLibrary* GetPhysicsAssetLibrary() { return physicsLibrary; }
	ComponentAssetLibrary* GetComponentAssetLibrary() { return componentLibrary; }
	ObjectAssetLibrary* GetObjectAssetLibrary() { return objectLibrary; }
	SoundAssetLibrary* GetSoundAssetLibrary() { return soundLibrary; }
	//Factory Getter
	ObjectFactory* GetObjectFactory() { return objectFactory; }

	//Other Getters
	GAME_INT GetGAME_FPS() { return GAME_FPS; }
	GAME_VEC GetcityCorner() { return cityCorner; }
	GAME_INT GetLevel() { return level; }
	bool GetLoadBasement() { return loadBasement; }

	//Setters
	
	//Devices
	void SetGraphicsDevice (GraphicsDevice * gDevice) {this->gDevice = gDevice;}
	void SetControllerDevice(ControllerDevice* cDevice) { this->cDevice = cDevice; }
	//void SetPhysicsDevice(PhysicsDevice* physDevice) { this->physicsDevice = physDevice; }
	void SetPhysicsDevice(PhysicsDevice* pDevice);
	void SetSoundDevice(SoundDevice* sDevice) { this->sDevice = sDevice; }
	
	//Libraries
	void SetArtAssetLibrary(ArtAssetLibrary* artLibrary) { this->artLibrary = artLibrary; }
	void SetPhysicsAssetLibrary(PhysicsAssetLibrary* physicsLibrary) { this->physicsLibrary = physicsLibrary; }
	void SetComponentAssetLibrary(ComponentAssetLibrary* componentLibrary) { this->componentLibrary = componentLibrary; }
	void SetObjectAssetLibrary(ObjectAssetLibrary* objectLibrary) { this->objectLibrary = objectLibrary; }
	void SetSoundAssetLibrary(SoundAssetLibrary* soundLibrary) { this->soundLibrary = soundLibrary; }
	
	//Factory
	void SetObjectFactory(ObjectFactory* objectFactory) { this->objectFactory = objectFactory; }
	
	//Other
	void SetFPS(GAME_INT GAME_FPS) { this->GAME_FPS = GAME_FPS; }
	void SetCityCorner(GAME_VEC cityCorner) { this->cityCorner = cityCorner; }
	void SetLevel(GAME_INT level) { this->level = level; }
	void SetLoadBasement(bool loadBasement) { this->loadBasement = loadBasement; }

	//Debug
	void PrintError() { printf("Failed to init at paused line\n"); system("pause"); exit(1); }



protected:
	//Devices
	GraphicsDevice * gDevice;
	ControllerDevice* cDevice;
	PhysicsDevice* physicsDevice;
	SoundDevice* sDevice;

	//Libraries
	ArtAssetLibrary* artLibrary;
	PhysicsAssetLibrary* physicsLibrary;
	ComponentAssetLibrary* componentLibrary;
	ObjectAssetLibrary* objectLibrary;
	SoundAssetLibrary* soundLibrary;

	ObjectFactory* objectFactory;

	GAME_INT GAME_FPS;
	GAME_VEC cityCorner;
	GAME_INT level;
	bool loadBasement;
	std::string spriteConfig;

};




#endif // RESOURCEMANAGER_H
