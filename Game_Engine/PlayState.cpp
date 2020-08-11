//Play State Source File

#include "PlayState.h"

//Initializing static member variable playID
const std::string PlayState::playID = "PLAY";

//Play State constructor
PlayState::PlayState(std::vector<GameObject*> parameter, void (*callBackFunction)(), void (*callBackFunction2)())
{
	for (int i = 0; i < parameter.size(); i++)
		gameObjects.push_back(parameter[i]);
	callback = callBackFunction;
	callback2 = callBackFunction2;
}

//Returns GameState ID
std::string PlayState::GetStateID() const
{
	return playID;
}

//Update Function of PlayState
void PlayState::Update(float dtAsSeconds)
{
	if (Keyboard::isKeyPressed(Keyboard::Escape))
		callback();
	for (int i = 2; i < gameObjects.size(); i++)
		gameObjects[i]->Update(dtAsSeconds);
	if (CheckCollision(gameObjects[2]->GetCollider(), gameObjects[3]->GetCollider()))
		callback2();
}

//Render function of PlayState
void PlayState::Render(RenderWindow* window)
{
	gameObjects[0]->DrawStill(window);
	for (int i = 2; i < gameObjects.size(); i++)
		gameObjects[i]->Draw(window);
}

//Function to be called when we enter Play State
bool PlayState::OnEnter()
{
	return true;
}

//Function to be called when we exit Play State
bool PlayState::OnExit()
{
	return true;
}

//Checks collision between 2 gameobjects
bool PlayState::CheckCollision(FloatRect* object1, FloatRect* object2)
{
	int leftA, leftB, rightA, rightB, topA, topB, bottomA, bottomB;
	/*leftA = object1->GetPosition().GetX();
	rightA = object1->GetPosition().GetX() + object1->GetWidth();
	topA = object1->GetPosition().GetY();
	bottomA = object1->GetPosition().GetY() + object1->GetHeight();
	leftB = object2->GetPosition().GetX();
	rightB = object2->GetPosition().GetX() + object2->GetWidth();
	topB = object2->GetPosition().GetY();
	bottomB = object2->GetPosition().GetY() + object2->GetHeight();
	if (rightA <= leftB)
		return false;
	if (leftA >= rightB)
		return false;
	return true;*/
	leftA = object1->left;
	rightA = object1->left + object1->width;
	topA = object1->top;
	bottomA = object1->top + object1->height;
	leftB = object2->left;
	rightB = object2->left + object2->width;
	topB = object2->top;
	bottomB = object2->top + object2->height;
	if (rightA <= leftB)
		return false;
	if (leftA >= rightB)
		return false;
	return true;
}