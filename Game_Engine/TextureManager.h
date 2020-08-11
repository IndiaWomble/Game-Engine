//Texture Manager Header File : To handle textures and sprites in the game

#pragma once

#ifndef __TextureManager_h__
#define __TextureManager_h__

#include "SFML/Graphics.hpp"

using namespace sf;

class TextureManager
{
	std::map<String, Sprite*> spriteMap;
	std::map<String, Texture*> textureMap;
	static TextureManager* instance;

	TextureManager();

public:
	bool Load(String fileName, std::string id);
	void Draw(String id, int x, int y, int width, int height, int left, int top, RenderWindow* window, float xScale = 1.0f, float yScale = 1.0f);
	void Animate(String id, int x, int y, IntRect sourceRect, RenderWindow* window, float xScale = 1.0f, float yScale = 1.0f);
	static TextureManager* Instance();
	void ClearFromTextureMap(std::string id);
	FloatRect GetCollider(std::string id);
};

#endif // !__TextureManager_h__
