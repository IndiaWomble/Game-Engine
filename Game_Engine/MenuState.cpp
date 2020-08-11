//Menu State Source File

#include "MenuState.h"

//Initializing static member variable menuID
const std::string MenuState::menuID = "MENU";

//Menu State constructor
MenuState::MenuState(std::string backgroundFileLocation, std::vector<GameObject*> parameter, void (*callBackFunction)())
{
	for (int i = 0; i < parameter.size(); i++)
		gameObjects.push_back(parameter[i]);
	TextureManager::Instance()->Load(backgroundFileLocation, "background");
	callBack = callBackFunction;
}

//Returns GameState ID
std::string MenuState::GetStateID() const
{
	return menuID;
}

//Update Function of MenuState
void MenuState::Update(float dtAsSeconds)
{
	if (Keyboard::isKeyPressed(Keyboard::Space))
		callBack();
}

//Render function of MenuState
void MenuState::Render(RenderWindow* window)
{
	TextureManager::Instance()->Draw("background", 0, 0, 280, 180, 0, 0, window, 16.0f, 11.0f);
	for (int i = 2; i < gameObjects.size(); i++)
		gameObjects[i]->Draw(window);
}

//Function to be called when we enter Menu State
bool MenuState::OnEnter()
{
	return true;
}

//Function to be called when we exit Menu State
bool MenuState::OnExit()
{
	for (int i = 0; i < gameObjects.size(); i++)
		gameObjects[i]->Clean();
	gameObjects.clear();
	TextureManager::Instance()->ClearFromTextureMap("background");
	return true;
}