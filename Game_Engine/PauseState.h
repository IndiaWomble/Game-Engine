//Pause State Header File

#pragma once

#ifndef __PauseState_h__
#define __PauseState_h__

#include "GameState.h"

class PauseState : public GameState
{
	static const std::string pauseID;
	std::vector<GameObject*> gameObjects;
	void (*callback)();

public:
	PauseState(std::vector<GameObject*> parameter, void (*callbackFunction)());
	virtual void Update(float dtAsSeconds);
	virtual void Render(RenderWindow* window);
	virtual bool OnEnter();
	virtual bool OnExit();
	virtual std::string GetStateID() const;
};

#endif // !__PauseState_h__
