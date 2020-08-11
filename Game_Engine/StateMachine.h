//State Machine Header File
//Implementing FSM(Finite State Machine)

#pragma once

#ifndef __StateMachine_h__
#define __StateMachine_h__

#include "GameState.h"
#include "MenuState.h"
#include "PlayState.h"
#include "PauseState.h"
#include "GameOver.h"
#include <vector>

class StateMachine
{
	std::vector<GameState*> gameStates;

public: 
	void PushState(GameState* state);
	void ChangeState(GameState* state);
	void PopState();
	void Update(float dtAsSeconds);
	void Render(RenderWindow* window);
};

#endif // !__StateMachine_h__
