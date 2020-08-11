//Texture Manager Source File

#include "TextureManager.h"
#include <iostream>

//To also be able to use TextureManager with the name SpriteManager
typedef TextureManager SpriteManager;

//Static instance varaible to maintain only one copy of this class
TextureManager* TextureManager::instance = nullptr;

//User-defined constructor
TextureManager::TextureManager()
{
	//Constructor
}

//Static member function to take care of single copy of class
TextureManager* TextureManager::Instance()
{
	if (instance == nullptr)
		instance = new TextureManager();
	return instance;
}

//To load texture and sprites and maps
bool TextureManager::Load(String fileName, std::string id)
{
	Texture* tempTexture = new Texture();
	tempTexture->loadFromFile(fileName);
	if (tempTexture == nullptr)
	{
		std::cout << id << std::endl;
		return false;
	}
	textureMap[id] = tempTexture;
	Sprite* tempSprite = new Sprite(*tempTexture);
	if (tempSprite != nullptr)
	{
		spriteMap[id] = tempSprite;
		return true;
	}
	std::cout << id << std::endl;
	return false;
}

//To draw sprites
void TextureManager::Draw(String id, int x, int y, int width, int height, int left, int top, RenderWindow* window, float xScale, float yScale)
{
	IntRect sourceRect, destinationRect;
	sourceRect.left = left;
	sourceRect.top = top;
	sourceRect.width = destinationRect.width = width;
	sourceRect.height = destinationRect.height = height;
	destinationRect.left = x;
	destinationRect.top = y;
	spriteMap[id]->setTextureRect(sourceRect);
	spriteMap[id]->setScale(xScale, yScale);
	spriteMap[id]->setPosition(destinationRect.left, destinationRect.top);
	window->draw(*spriteMap[id]);
}

//To draw animated sprites/spritesheet
void TextureManager::Animate(String id, int x, int y, IntRect sourceRect, RenderWindow* window, float xScale, float yScale)
{
	spriteMap[id]->setScale(xScale, yScale);
	spriteMap[id]->setPosition(x, y);
	spriteMap[id]->setTextureRect(sourceRect);
	window->draw(*spriteMap[id]);
}

//To delete texture from texture map
void TextureManager::ClearFromTextureMap(std::string id)
{
	textureMap.erase(id);
}

//To return collider of sprite
FloatRect TextureManager::GetCollider(std::string id)
{
	return spriteMap[id]->getGlobalBounds();
}