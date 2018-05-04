///////////////////////////////////////
//Author:		Nicholas Larsen
//
//Date:			5/2/2018
//
//Header File:	ArtAssetLibrary.h
//
//Purpose:		Contain sprites for
//				quick reference
////////////////////////////////////////

#include "Define.h"
#include "ArtAssetLibrary.h"

ArtAssetLibrary::ArtAssetLibrary()
{

}
bool ArtAssetLibrary::Initialize(GraphicsDevice* gDevice)
{
	this->gDevice = gDevice;
}
Texture* ArtAssetLibrary::Search(std::string key)
{
	return (artLibrary.find(key)->second);
}
bool ArtAssetLibrary::AddAsset(std::string name, std::string path)
{
	Texture* tempTexture;
	TiXmlDocument spriteConfig(path);
	if (!spriteConfig.LoadFile()) { return false; }
	//<Sprites>
	TiXmlElement* spriteRoot = spriteConfig.FirstChildElement();
	//<Sprite name= sheet= alphaR|G|B= numStates=>
	////<State>
	//////<Clip>
	TiXmlElement* spriteElement = spriteRoot->FirstChildElement();

	/*Load textures into tempTextures to add to artLibrary*/
	do
	{
		Texture* tmpTexture = new Texture();
		if (name == spriteElement->Attribute("name"))
		{
			artLibrary[name] = new Texture();
			artLibrary[name]->XMLLoad(gDevice->GetRenderer(), spriteElement);
		}
		else
		{
			spriteElement->NextSiblingElement();
		}

	} while (spriteElement);
	if (artLibrary[name] == nullptr)
	{
		printf("error loading texture\n");
		system("pause");
	}



	/*if (!tempTexture->load(gDevice->GetRenderer(), texturePath)) { return false; }*/
	//add to library


}