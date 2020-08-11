//Menu State Header file

#pragma once

#ifndef __MenuState_h__
#define __MenuState_h__

#include "GameState.h"

class MenuState : public GameState, public GameObject
{
	static const std::string menuID;
	std::vector<GameObject*> gameObjects;
	void (*callBack)();

public:
	MenuState(std::string backgroundFileLocation, std::vector<GameObject*> parameter, void (*callBackFunction)());
	virtual void Update(float dtAsSeconds);
	virtual void Render(RenderWindow* window);
	virtual bool OnEnter();
	virtual bool OnExit();
	virtual std::string GetStateID() const;
};

#endif // !__MenuState_h__