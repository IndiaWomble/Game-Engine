//Game Over Header File

#pragma once

#ifndef __GameOver_h__
#define __GameOver_h__

#include "GameState.h"

class GameOverState : public GameState
{
	static const std::string gameOverID;
	std::vector<GameObject*> gameObjects;
	void (*callback)();
	float sleepTime;

public:
	GameOverState(std::vector<GameObject*> parameter, void (*callbackFunction)());
	virtual void Update(float dtAsSeconds);
	virtual void Render(RenderWindow* window);
	virtual bool OnEnter();
	virtual bool OnExit();
	virtual std::string GetStateID() const;
};

#endif // !__GameOver_h__