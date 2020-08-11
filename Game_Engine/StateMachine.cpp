//State Machine Source File

#include "StateMachine.h"

//To add new game state
void StateMachine::PushState(GameState* state)
{
	gameStates.push_back(state);
	gameStates.back()->OnEnter();
}

//To remove state
void StateMachine::PopState()
{
	if (!gameStates.empty())
		if (gameStates.back()->OnExit())
		{
			delete gameStates.back();
			gameStates.pop_back();
		}
}

//To change to another state
void StateMachine::ChangeState(GameState* state)
{
	if (!gameStates.empty())
	{
		if (gameStates.back()->GetStateID() == state->GetStateID())
			return;
		if (gameStates.back()->OnExit())
		{
			delete gameStates.back();
			gameStates.pop_back();
		}
	}
	gameStates.push_back(state);
	gameStates.back()->OnEnter();
}

//Calls Update Function of the respective states
void StateMachine::Update(float dtAsSeconds)
{
	if (!gameStates.empty())
		gameStates.back()->Update(dtAsSeconds);
}

//Calls Render Function of the respective states
void StateMachine::Render(RenderWindow* window)
{
	if (!gameStates.empty())
		gameStates.back()->Render(window);
}