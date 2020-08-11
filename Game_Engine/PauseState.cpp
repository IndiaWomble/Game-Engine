//Pause State source file

#include "PauseState.h"

//Instantiating static variable pauseID
const std::string PauseState::pauseID = "PAUSE";

//Pause State constructor
PauseState::PauseState(std::vector<GameObject*> parameter, void (*callbackFunction)())
{
	for (int i = 0; i < parameter.size(); i++)
		gameObjects.push_back(parameter[i]);
	callback = callbackFunction;
}

//Return state ID
std::string PauseState::GetStateID() const
{
	return pauseID;
}

//Update function of Pause State
void PauseState::Update(float dtAsSeconds)
{
	if (Keyboard::isKeyPressed(Keyboard::Space))
		callback();
}

//Render function of Pause State
void PauseState::Render(RenderWindow* window)
{
	gameObjects[0]->DrawStill(window);
	for (int i = 2; i < gameObjects.size(); i++)
		gameObjects[i]->Draw(window);
}

//First fucntion to be called when we enter Pause State
bool PauseState::OnEnter()
{
	return true;
}

//Last function to be called wehen we exit Pause State
bool PauseState::OnExit()
{
	for (int i = 0; i < gameObjects.size(); i++)
		gameObjects[i]->Clean();
	gameObjects.clear();
	return true;
}