//Engine Header File

#pragma once

#ifndef __Engine_h__
#define __Engine_h__

#include <vector>
#include "GameObject.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "StateMachine.h"

class Engine
{
	bool running, mouseMovementRequired;
	int currentFrame, frameWidth, numberOfFrames;
	RenderWindow* window;
	static Engine* instance;
	std::vector<GameObject*> gameObjects;
	StateMachine* stateMachine;
	std::string backgroundLocation;

	Engine();
	static void MenuToPlay();
	static void Pause();
	static void ResumePlay();
	static void RestartPlay();
	static void GameOver();

public:
	~Engine();
	bool Initialize(String windowTitle, bool fullScreen, std::string backgroundFileLocation, bool mouseMovement = false);
	void Render();
	void Update(float dtAsSeconds);
	void HandleEvents();
	void Clean();
	bool IsRunning();
	static Engine* Instance();
	RenderWindow* GetWindow() const;
	void AddGameObject(GameObject* gameObject);
	void StartGameLoop();
	StateMachine* GetStateMachine();
};

#endif // !__Engine_h__