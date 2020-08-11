// Main Source File For Testing

#include "Engine.h"

/*
User Guide : 
1. Create a new Loader object to load GameObjects
2. Create GameObjects using the respective classes (GameObject class, Player class, Enemy class)
3. Add the created GameObjects to the Engine using "AddGameObject()" function of Engine class
4. After adding all the GameObjects to the Engine, delete Loader object
5. Instantiate Engine
6. Start Game Loop using function "StartGameLoop()" of Engine class
7. Open GameObject.cpp file to edit the behaviors of GameObjects, Player and Enemies by editing their Update function
*/

int main(int argc, char* argv[])
{
	Loader* loader = new Loader("D:/C++/Game Engine/Test Assets/images.png", "background1", 280, 180, 16.0f, 11.0f);
	GameObject* background = new GameObject(loader);
	Engine::Instance()->AddGameObject(background);
	delete loader;
	loader = new Loader("D:/C++/Game Engine/Test Assets/gameover.png", "gameover", 280, 180, 16.0f, 11.0f);
	GameObject* gameOver = new GameObject(loader);
	Engine::Instance()->AddGameObject(gameOver);
	delete loader;
	loader = new Loader(false, true, 550, 1620, 23, 25, 6, 6, 54.0f, 265.0f, 317.0f, 3, "player",
		"D:/C++/Game Engine/Test Assets/Nintendo Switch - Super Mario Odyssey - Mario 2D(840x859).png", 551, 54, 499, "flippedPlayer",
		"D:/C++/Game Engine/Test Assets/Nintendo Switch - Super Mario Odyssey - Mario 2D(840x859)flip.png");
	Player* player = new Player(loader);
	Engine::Instance()->AddGameObject(player);
	delete loader;
	loader = new Loader(false, false, 1000, 1650, 10, 12, 11, 10, 2.0f, 0.0f, 20.0f, 10, "enemy",
		"D:/C++/Game Engine/Test Assets/enemy sprite sheet (290x174).png");
	Enemy* enemy = new Enemy(loader);
	Engine::Instance()->AddGameObject(enemy);
	delete loader;
	if (Engine::Instance()->Initialize("Mario", false, "D:/C++/Game Engine/Test Assets/Start.png"))
		Engine::Instance()->StartGameLoop();
	else
		return -1;
	return 0;
}