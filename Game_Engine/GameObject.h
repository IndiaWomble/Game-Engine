//GameObject Header File

#pragma once

#ifndef __GameObject_h__
#define __GameObject_h__

#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "InputHandler.h"

//Header file to load data into objects of respective classes
class Loader
{
	int x, y, sourceRectWidth, sourceRectHeight, destinationRectWidth, destinationRectHeight, specialAnimationFactor, flippedLeft, flippedTop, 
		flippedLeftOfLastFrame;
	float row, frame, leftLastFrame;
	std::string textureID, flippedTextureID, path, flippedPath;
	bool isAcceleratingGameObject, flippingRequired;

public:
	Loader(bool isAccelerating, bool flipable, int parameterX, int parameterY, int parameterSourceWidth, int parameterSourceHeight, 
		int parameterDestinationWidth, int parameterDestinationHeight, float parameterRow, float parameterFrame, float parameterLeftLastFrame, 
		int specialAnimationFactor, std::string parameterTextureID, std::string parameterPath, int parameterFlippedLeft = NULL, 
		int parameterFlippedTop = NULL, int flippedLastFrame = NULL, std::string flipTextureID = "\0", std::string parameterFlipPath = "\0");
	Loader(std::string parameterPath, std::string id, int width, int height, float scaleX, float scaleY);
	int GetX() const;
	int GetY() const;
	int GetSourceWidth() const;
	int GetSourceHeight() const;
	int GetDestinationWidth() const;
	int GetDestinationHeight() const;
	int GetAnimationFactor() const;
	int GetFlippedLeft() const;
	int GetFlippedTop() const;
	int GetFlippedLastFrame() const;
	float GetRow() const;
	float GetFrame() const;
	float GetLeftLastFrame() const;
	std::string GetTextureID() const;
	std::string GetPath() const;
	std::string GetFlippedTextureID() const;
	std::string GetFlippedPath() const;
	bool GetObjectType() const;
 	bool GetFlipStatus() const;
};

//Abstract GameObject Class. All other GameObject-related classes are derived from this class. It provides the basic skeletal for GameObject classes.
class Abstract_Game_Object
{
protected:
	Abstract_Game_Object() = default;
	Abstract_Game_Object(const Loader* parameters);
	virtual ~Abstract_Game_Object() {};

public:
	virtual void Draw(RenderWindow* window) = 0;
	virtual void Update(float dtAsSeconds) = 0;
	virtual void Clean() = 0;
};

//Main GameObject Class
class GameObject : public Abstract_Game_Object
{
	float time, frameSpeed;

protected:
	int destinationRectWidth, destinationRectHeight, specialAnimationFactor, flippedLastFrame, currentFlippedFrame;
	float currentFrame, leftOfLastFrame;
	std::string textureID, flippedTextureID;
	Vector2D position, velocity, acceleration;
	bool isAcceleratingGameObject, canBeFlipped;
	IntRect sourceRect, flippedSourceRect;
	FloatRect collider;

public:
	GameObject() = default;
	GameObject(const Loader* parameters);
	virtual void Draw(RenderWindow* window);
	virtual void Update(float dtAsSeconds);
	virtual void Clean();
	Vector2D& GetPosition();
	int GetWidth();
	int GetHeight();
	void DrawStill(RenderWindow* window);
	FloatRect* GetCollider();
};

//A subdivision of GameObject class (Player)
class Player : public GameObject
{
	void HandleInput();
public:
	Player(const Loader* parameters);
	virtual void Draw(RenderWindow* window);
	virtual void Update(float dtAsSeconds);
	virtual void Clean();
};

//A subdivision of GameObject class (Enemy)
class Enemy : public GameObject
{
public:
	Enemy(const Loader* parameters);
	virtual void Draw(RenderWindow* window);
	virtual void Update(float dtAsSeconds);
	virtual void Clean();
};

//Animation speed controlled gameobjects
class AnimatedGraphic : public GameObject
{
	int animationSpeed;

public:
	AnimatedGraphic(const Loader* parameters, int parameterAnimationSpeed);
	void Update(float dtAsSeconds);
};

#endif // !__GameObject_h__