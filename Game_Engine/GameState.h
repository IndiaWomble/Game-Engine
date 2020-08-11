//Game State Abstract Header File

#pragma once

#ifndef __GameState_h__
#define __GameState_h__

#include <string>
#include "GameObject.h"

class GameState
{
public:
	virtual void Update(float dtAsSeconds) = 0;
	virtual void Render(RenderWindow* window) = 0;
	virtual bool OnEnter() = 0;
	virtual bool OnExit() = 0;
	virtual std::string GetStateID() const = 0;
};

#endif // !__GameState_h__
