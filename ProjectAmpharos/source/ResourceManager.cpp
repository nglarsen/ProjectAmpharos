///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:			5/2/2018
//
//Header File:	ResourceManager.h
//
//Purpose:		Handle devices and resources
//				centrally
////////////////////////////////////////

#include "Define.h"
#include "ResourceManager.h"
#include "ObjectFactory.h"
#include "tinyxml\tinyxml.h"
#include "Box2DDebugDraw.h"

ResourceManager::ResourceManager()
{

}
ResourceManager::~ResourceManager()
{
	delete objectFactory;
}

bool ResourceManager::Initialize(GAME_INT SCREEN_WIDTH, GAME_INT SCREEN_HEIGHT, std::string assetPath)
{
	//TODO: Make this something
	loadBasement = false;


	GAME_FPS = 100;
	//=====================================
	//Construct Object Factory
	//=====================================
	objectFactory = new ObjectFactory();
	
	//=====================================
	//Construct Controller
	//=====================================
	cDevice = new ControllerDevice();
	if (!cDevice->Initialize())
	{
		PrintError();
	}
	
	//=====================================
	//Construct Graphics Device
	//=====================================
	gDevice = new GraphicsDevice(SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!gDevice->Initialize(false))
	{
		PrintError();
	}
	//=====================================
	//Set Font for Graphics Device:
	//=====================================

	GAME_RGBA RGBA;
	RGBA.R = 0;
	RGBA.G = 0;
	RGBA.B = 0;
	RGBA.A = 255;

	gDevice->SetFont("./Assets/Fonts/impact.ttf", 16, RGBA);
	//=====================================
	//Construct Physics Device:
	//=====================================
	physicsDevice = new PhysicsDevice(0,0);

	if (!physicsDevice->Initialize())
	{
		PrintError();
	}
	//=====================================
	//Construct Sound Device
	//=====================================
	sDevice = new SoundDevice();

	if (!sDevice->Initialize())
	{
		PrintError();
	}
	//=====================================
	//Construct ArtLibrary
	//=====================================
	artLibrary = new ArtAssetLibrary();
	spriteConfig = "./Assets/Config/SpriteConfig.xml";
	if (!artLibrary->Initialize(gDevice))
	{
		PrintError();
	}
	//=====================================
	//Construct Physics Library
	//=====================================
	physicsLibrary = new PhysicsAssetLibrary();

	if (!physicsLibrary->Initialize())
	{
		PrintError();
	}
	//=====================================
	//Construct Component Library
	//=====================================
	componentLibrary = new ComponentAssetLibrary();

	if (!componentLibrary->Initialize())
	{
		PrintError();
	}
	////=====================================
	////Construct Object Library
	////=====================================
	//objectLibrary = new ObjectAssetLibrary();

	//if (!objectLibrary->Initialize())
	//{
	//	PrintError();
	//}
	//=====================================
	//Construct Sound Library
	//=====================================
	soundLibrary = new SoundAssetLibrary();

	if(!soundLibrary->Initialize(sDevice))
	{
		PrintError();
	}
	
	//=====================================
	//Populate Libraries
	//=====================================
	
	//Prepare XML for Parsing
	TiXmlDocument assetFile(assetPath);
	if (!assetFile.LoadFile()) { return false; }
	//Grab the Root <Assets>
	TiXmlElement* assetType = assetFile.FirstChildElement();
	//Grab the first asset/object
	//i.e.<GameAsset name="Block">
	TiXmlElement* asset = assetType->FirstChildElement();

	do
	{
		//Get the Asset name
		std::string assetName = asset->Attribute("name");

		//where we will store the components:
		std::vector<GAME_COMPONENT_LIST> componentList;

		//move to the components of the xml
		//i.e. <Component name="Sprite">
		//Current options:	Body|Controller|ItemBlock
		//					PowerUp|Sprite|
		TiXmlElement* compElement = asset->FirstChildElement();

		//Add each component to the vector
		while (compElement)
		{
			//Get the component's name
			std::string currentComponent = compElement->Attribute("name");
			//find the component
			if (currentComponent == "Body")
			{
				GAME_PHYSICS physics;
				compElement->QueryFloatAttribute("density", &physics.density);
				compElement->QueryFloatAttribute("restitution", &physics.restitution);
				compElement->QueryFloatAttribute("angularDamping", &physics.angularDamping);
				compElement->QueryBoolAttribute("physicsOn", &physics.physicsOn);
				std::string bodyType;
				std::string bodyShape;
				compElement->QueryStringAttribute("bodyType", &bodyType);
				compElement->QueryStringAttribute("bodyShape", &bodyShape);

				if (bodyType == "GAME_DYNAMIC") { physics.bodyType = GAME_DYNAMIC; }
				else if (bodyType == "GAME_KINEMATIC") { physics.bodyType = GAME_KINEMATIC; }
				else if (bodyType == "GAME_STATIC") { physics.bodyType = GAME_STATIC; }

				if (bodyShape == "GAME_RECTANGLE") { physics.bodyShape = GAME_RECTANGLE; }
				else if (bodyShape == "GAME_CIRCLE") { physics.bodyShape = GAME_CIRCLE; }

				physicsLibrary->AddAsset(assetName, physics);
				componentList.push_back(GAME_BODY_COMP);

			}
			else if(currentComponent == "Controller")
			{
				componentList.push_back(GAME_CONTROL_COMP);
			}
			else if (currentComponent == "ItemBlock") 
			{
				componentList.push_back(GAME_ITEMBLOCK_COMP);
			}
			else if (currentComponent == "PowerUp")
			{
				componentList.push_back(GAME_POWERUP_COMP);
			}
			else if (currentComponent == "Sprite") 
			{
				artLibrary->AddAsset(assetName, spriteConfig);
				componentList.push_back(GAME_SPRITE_COMP);
			}

			else
			{
				printf("INVALID component in assets.xml %s", currentComponent.c_str());
				return false;
			}
			compElement = compElement->NextSiblingElement();
		}
		if (componentList.empty()) { return false; }
		componentLibrary->AddAsset(assetName, componentList);
		
		asset = asset->NextSiblingElement();
	} while (asset);
	assetType = assetType->NextSiblingElement();

	TiXmlElement* sounds = assetType->FirstChildElement();
	
	while (sounds)
	{
		std::string name;
		sounds->QueryStringAttribute("name", &name);
		std::string path;
		sounds->QueryStringAttribute("path", &path);
		bool background;
		sounds->QueryBoolAttribute("background", &background);

		//add to library based on background music or not.
		if (background)
		{
			soundLibrary->AddBackgroundMusic(name, path);
		}
		else
		{
			soundLibrary->AddSoundEffect(name, path);
		}
		sounds = sounds->NextSiblingElement();
	}

	//======================================
	//Set up debugging
	//======================================



	Box2DDebugDraw* debugDraw = new Box2DDebugDraw();
	debugDraw->Initialize(this);
	debugDraw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_aabbBit);

	if (debugDraw != NULL)
	{
		physicsDevice->getWorld()->SetDebugDraw(debugDraw);
	}
	return true;
}

bool ResourceManager::ShutDown()
{
	cDevice = nullptr;
	
	soundLibrary->Finish();
	soundLibrary = NULL;

	gDevice->ShutDown();
	gDevice = NULL;

	sDevice->ShutDown();
	sDevice = NULL;

	physicsDevice = NULL;

	artLibrary = NULL;
	physicsLibrary = NULL;
	objectLibrary = NULL;

	objectFactory = NULL;

	return true;
}

void ResourceManager::SetPhysicsDevice(PhysicsDevice * pDevice)
{
	this->physicsDevice = pDevice;
}
