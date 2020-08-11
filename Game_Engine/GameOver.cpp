//Game Over State source file

#include "GameOver.h"

//Instantiating static variable gameOverID
const std::string GameOverState::gameOverID = "GAMEOVER";

//GameOver State constructor
GameOverState::GameOverState(std::vector<GameObject*> parameter, void (*callbackFunction)())
{
	for (int i = 0; i < parameter.size(); i++)
		gameObjects.push_back(parameter[i]);
	callback = callbackFunction;
	sleepTime = 0.0f;
}

//Return state ID
std::string GameOverState::GetStateID() const
{
	return gameOverID;
}

//Update function of GameOver State
void GameOverState::Update(float dtAsSeconds)
{
	//Find a way to change state to play state and revert back all the updates to the initial values
	/*sleepTime += dtAsSeconds;
	if (sleepTime > 2)
		callback();*/
}

//Render function of GameOver State
void GameOverState::Render(RenderWindow* window)
{
	gameObjects[1]->DrawStill(window);
}

//First function to be called when we enter GameOver State
bool GameOverState::OnEnter()
{
	return true;
}

//Last function to be called when we exit GameOver State
bool GameOverState::OnExit()
{
	for (int i = 0; i < gameObjects.size(); i++)
		gameObjects[i]->Clean();
	gameObjects.clear();
	return true;
}