//Play State Header File

#pragma once

#ifndef __PlayState_h__
#define __PlayState_h__

#include "GameState.h"

class PlayState : public GameState
{
	static const std::string playID;
	std::vector<GameObject*> gameObjects;
	
	void (*callback)();
	void (*callback2)();

public:
	PlayState(std::vector<GameObject*> parameter, void (*callbackFunction)(), void (*callBackFunction2)());
	virtual void Update(float dtAsSeconds);
	virtual void Render(RenderWindow* window);
	virtual bool OnEnter();
	virtual bool OnExit();
	virtual std::string GetStateID() const;
	bool CheckCollision(FloatRect* object1, FloatRect* object2);
};

#endif // !__PlayState_h__
