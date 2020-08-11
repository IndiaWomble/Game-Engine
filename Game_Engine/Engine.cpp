//Engine Source File

#include "Engine.h"

//Engine may also be called as GameManager
typedef Engine GameManager;

//Static variable instance declaration
Engine* Engine::instance = nullptr;

//Constructor to initialize all data members
Engine::Engine()
{
	running = mouseMovementRequired = false;
	window = nullptr;
	stateMachine = nullptr;
	currentFrame = 0;
	frameWidth = numberOfFrames = 1;
}

//Destructor to take care of accidental undeleted data members
Engine::~Engine()
{
	running = false;
}

//To make Engine class static
Engine* Engine::Instance()
{
	if (instance == nullptr)
		instance = new Engine();
	return instance;
}

//Creates window and places a background image
bool Engine::Initialize(String windowTitle, bool fullScreen, std::string backgroundFileLocation, bool mouseMovement)
{
	window = new RenderWindow();
	window->create(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), windowTitle, 
		fullScreen ? Style::Fullscreen | Style::Default : Style::Default);
	if (window != nullptr)
	{
		window->setFramerateLimit(60);
		mouseMovementRequired = mouseMovement;
		InputHandler::Instance()->InitializeJoysticks();
		running = true;
		backgroundLocation = backgroundFileLocation;
		stateMachine = new StateMachine();
		stateMachine->ChangeState(new MenuState(backgroundFileLocation, gameObjects, MenuToPlay));
		return true;
	}
	else
		return false;
}

//Renders all gameobjects to the window
void Engine::Render()
{
	window->clear();
	stateMachine->Render(window);
	window->display();
}

//Updates all variables 
void Engine::Update(float dtAsSeconds)
{
	stateMachine->Update(dtAsSeconds);
}

//Handles user input
void Engine::HandleEvents()
{
	Event event;
	while (window->pollEvent(event))
	{
		if (event.type == Event::Closed)
			running = false;
		else
			InputHandler::Instance()->Update(event, mouseMovementRequired);
	}
}

//Garbage Cleaning function
void Engine::Clean()
{
	InputHandler::Instance()->Clean();
	window->close();
	delete window;
}

//Member variable accessing function
bool Engine::IsRunning()
{
	return running;
}

//To return window
RenderWindow* Engine::GetWindow() const
{
	return window;
}

//To Start the main game loop
void Engine::StartGameLoop()
{
	Clock* clock = new Clock();
	while (IsRunning())
	{
		Time dt = clock->restart();
		float dtAsSeconds = dt.asSeconds();
		HandleEvents();
		Update(dtAsSeconds);
		Render();
	}
	Clean();
	delete clock;
}

//To add GameObjects
void Engine::AddGameObject(GameObject* gameObject)
{
	gameObjects.push_back(gameObject);
}

//Menu to play state changing callback function
void Engine::MenuToPlay()
{
	instance->stateMachine->ChangeState(new PlayState(instance->gameObjects, Pause, GameOver));
}

//Returns State Machine
StateMachine* Engine::GetStateMachine()
{
	return stateMachine;
}

//Callback function to resume play state
void Engine::ResumePlay()
{
	instance->stateMachine->PopState();
}

//Callback function to pause the game
void Engine::Pause()
{
	instance->stateMachine->PushState(new PauseState(instance->gameObjects, ResumePlay));
}

//Callback function to restart playstate 
void Engine::RestartPlay()
{
	instance->stateMachine->ChangeState(new PlayState(instance->gameObjects, Pause, GameOver));
}

//Callback function to trigger gameover scene
void Engine::GameOver()
{
	instance->stateMachine->ChangeState(new GameOverState(instance->gameObjects, MenuToPlay));
}