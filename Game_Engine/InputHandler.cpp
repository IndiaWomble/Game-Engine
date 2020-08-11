//Input Handler Source file

#include "InputHandler.h"

//InputHandler class can also be called as Input class
typedef InputHandler Input;

//Initiating static varibale instance
InputHandler* InputHandler::instance = nullptr;

//InputHandler constructor
InputHandler::InputHandler()
{
	for (int i = 0; i < 3; i++)
		mouseButtonStates.push_back(false);
	joysticksInitialized = false;
	mousePosition = nullptr;
}

//To make InputHandler Singleton
InputHandler* InputHandler::Instance()
{
	if (instance == nullptr)
		instance = new InputHandler();
	return instance;
}

//Manages Inputs from various devices
void InputHandler::Update(Event e, bool mouseMoveEnabled)
{
	switch (e.type)
	{
		case Event::JoystickMoved:
		{
			OnJoystickAxisMove(e);
			break;
		}
		case Event::JoystickButtonPressed:
		{
			OnJoystickButtonDown(e);
			break;
		}
		case Event::JoystickButtonReleased:
		{
			OnJoystickButtonDown(e);
			break;
		}
		case Event::MouseButtonPressed:
		{
			OnMouseButtonDown(e);
			break;
		}
		case Event::MouseButtonReleased:
		{
			OnMouseButtonUp(e);
			break;
		}
		case Event::MouseMoved:
		{
			if(mouseMoveEnabled)
				OnMouseMove(e);
			break;
		}
		default:
			break;
	}
}

//Deletes all joysticks when disconnected
void InputHandler::Clean()
{
	if (joysticksInitialized)
		for (unsigned int i = 0; i < joysticks.size(); i++)
			joysticks.pop_back();
}

//Initializes all joysticks attached
void InputHandler::InitializeJoysticks()
{
	for (int i = 0; i < 8; i++)
		if (Joystick::isConnected(i))
		{
			joysticks.push_back(&i);
			joystickValues.push_back(std::make_pair(new Vector2D(0, 0), new Vector2D(0, 0)));
			std::vector<bool> tempButtons;
			for (int j = 0; j < Joystick::getButtonCount(i); i++)
				tempButtons.push_back(false);
			buttonStates.push_back(tempButtons);
		}
		else
			break;
	joysticksInitialized = true;
	if (joysticks.size() == 0)
		joysticksInitialized = false;
}

//Returns if all joysticks are properly initialized
bool InputHandler::JoysticksInitialized()
{
	return joysticksInitialized;
}

//Returns x value of the given joystick and the given stick
int InputHandler::XValue(int joystick, int stick)
{
	if (joystickValues.size() > 0)
	{
		if (stick == 1)
			return joystickValues[joystick].first->GetX();
		else if (stick == 2)
			return joystickValues[joystick].second->GetX();
	}
	return 0;
}

//Returns y value of the given joystick and the given stick
int InputHandler::YValue(int joystick, int stick)
{
	if (joystickValues.size() > 0)
	{
		if (stick == 1)
			return joystickValues[joystick].first->GetY();
		else if (stick == 2)
			return joystickValues[joystick].second->GetY();
	}
	return 0;
}

//Returns if the the given button on the given joystick is pressed or not 
bool InputHandler::GetButtonState(int joystick, int buttonNumber)
{
	return buttonStates[joystick][buttonNumber];
}

//Returns if the given mouse button is pressed or not
bool InputHandler::GetMouseButtonState(int buttonNumber)
{
	return mouseButtonStates[buttonNumber];
}

//Returns mouse position
Vector2D* InputHandler::GetMousePosition()
{
	return mousePosition;
}

//Handles mouse movement event
void InputHandler::OnMouseMove(Event& event)
{
	mousePosition->SetX(event.mouseMove.x);
	mousePosition->SetY(event.mouseMove.y);
}

//Handles mouse button click events
void InputHandler::OnMouseButtonDown(Event& event)
{
	if (event.mouseButton.button == Mouse::Left)
		mouseButtonStates[LEFT] = true;
	if (event.mouseButton.button == Mouse::Middle)
		mouseButtonStates[MIDDLE] = true;
	if (event.mouseButton.button == Mouse::Right)
		mouseButtonStates[RIGHT] = true;
}

//Handles mouse button released events
void InputHandler::OnMouseButtonUp(Event& event)
{
	if (event.mouseButton.button == Mouse::Left)
		mouseButtonStates[LEFT] = false;
	if (event.mouseButton.button == Mouse::Middle)
		mouseButtonStates[MIDDLE] = false;
	if (event.mouseButton.button == Mouse::Right)
		mouseButtonStates[RIGHT] = false;
}

//Handles joystick stick movement events
void InputHandler::OnJoystickAxisMove(Event& event)
{
	int whichOne = event.joystickMove.joystickId;
	if (event.joystickMove.axis == 0)
	{
		if (event.joystickMove.position > joystickDeadZone)
			joystickValues[whichOne].first->SetX(1);
		else if (event.joystickMove.position < -joystickDeadZone)
			joystickValues[whichOne].first->SetX(-1);
		else
			joystickValues[whichOne].first->SetX(0);
	}
	if (event.joystickMove.axis == 1)
	{
		if (event.joystickMove.position > joystickDeadZone)
			joystickValues[whichOne].first->SetY(1);
		else if (event.joystickMove.position < -joystickDeadZone)
			joystickValues[whichOne].first->SetY(-1);
		else
			joystickValues[whichOne].first->SetY(0);
	}
	if (event.joystickMove.axis == 3)
	{
		if (event.joystickMove.position > joystickDeadZone)
			joystickValues[whichOne].second->SetX(1);
		else if (event.joystickMove.position < -joystickDeadZone)
			joystickValues[whichOne].second->SetX(-1);
		else
			joystickValues[whichOne].second->SetX(0);
	}
	if (event.joystickMove.axis == 4)
	{
		if (event.joystickMove.position > joystickDeadZone)
			joystickValues[whichOne].second->SetY(1);
		else if (event.joystickMove.position < -joystickDeadZone)
			joystickValues[whichOne].second->SetY(-1);
		else
			joystickValues[whichOne].second->SetY(0);
	}
}

//Handles joystick button click events
void InputHandler::OnJoystickButtonDown(Event& event)
{
	int whichOne = event.joystickButton.joystickId;
	buttonStates[whichOne][event.joystickButton.button] = true;
}

//Handles joystick button released events
void InputHandler::OnJoystickButtonUp(Event& event)
{
	int whichOne = event.joystickButton.joystickId;
	buttonStates[whichOne][event.joystickButton.button] = false;
}