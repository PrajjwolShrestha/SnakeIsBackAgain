#include "Constant.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "MySnake.h"
#include <SDL_mixer.h>

#include "SoundManager.h"
#include "SnakeObstacles.h"
#include "GameObject.h"


using namespace std;

class SnakeGameFunctions {

public:
	SnakeGameFunctions();
	~SnakeGameFunctions();

	//new added
	//function to start the game
	//loads up window, renderer,fonts and music for our snake game
	void gameInit(const char * gameTitle, int xPosition, int yPosition, int width, int height, bool maximised);
	//funtion that handles the control of snake
	void keyboardHandler(); //keyboard handling to control our snake
	void updateEverything(); //function to check our snake is still alive or not and update everything
	void render(); //render our snake at X and Y pos of screen
	void freeMemory(); //function that cleans up junk memory
	bool gameIsRunning() { return gameRunning; } //check if game is running or not

	//private attributes and pointers
private:
	SDL_Window * gameWindow;  //our game window
	SDL_Renderer * snakeRenderer; //renderer to render snake
	bool gameRunning = true; //boolean attribute
	MySnake * mySnake; //our snake object
	GameObject * gameObject; //gameobject

};