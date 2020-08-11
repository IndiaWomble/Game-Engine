//Input Handling Header File

#pragma once

#ifndef __InputHandler_h__
#define __InputHandler_h__

const int joystickDeadZone = 10000;

#include <vector>
#include "SFML/Graphics.hpp"
#include "Vector2D.h"

using namespace sf;

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
	InputHandler();
	~InputHandler();

	static InputHandler* instance;
	std::vector<int*> joysticks;
	std::vector<std::pair<Vector2D*, Vector2D*>> joystickValues;
	std::vector<std::vector<bool>> buttonStates;
	std::vector<bool> mouseButtonStates;
	bool joysticksInitialized;
	Vector2D* mousePosition;

public:
	static InputHandler* Instance();
	void Update(Event e, bool mouseMoveEnabled);
	void Clean();
	void InitializeJoysticks();
	bool JoysticksInitialized();
	int XValue(int joystick, int stick);
	int YValue(int joystick, int stick);
	bool GetButtonState(int joystick, int buttonNumber);
	bool GetMouseButtonState(int buttonNumber);
	Vector2D* GetMousePosition();
	void OnMouseMove(Event& event);
	void OnMouseButtonDown(Event& event);
	void OnMouseButtonUp(Event& event);
	void OnJoystickAxisMove(Event& event);
	void OnJoystickButtonDown(Event& event);
	void OnJoystickButtonUp(Event& event);
};

#endif // !__InputHandler_h__