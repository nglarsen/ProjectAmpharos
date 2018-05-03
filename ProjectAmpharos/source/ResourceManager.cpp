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
	gDevice = new GraphicsDevice();
	if (!gDevice->Initialize())
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
	pDevice = new PhysicsDevice();

	if (!pDevice->Initialize())
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
	//=====================================
	//Construct Object Library
	//=====================================
	objectLibrary = new ObjectAssetLibrary();

	if (!objectLibrary->Initialize())
	{
		PrintError();
	}
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

			}
			else if(currentComponent == "Controller")
			{
			
			}
			else if (currentComponent == "ItemBlock") 
			{
			
			}
			else if (currentComponent == "PowerUp")
			{
			
			}
			else if (currentComponent == "Sprite") 
			{
				artLibrary->AddAsset(assetName, spriteConfig);
				componentList.push_back(GAME_SPRITE_COMP);
			}
		}

		
	}

}