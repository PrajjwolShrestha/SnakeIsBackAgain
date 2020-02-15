#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h> //sdl image library to work with images
#include <cstdlib>
#include "Constant.h"  //constant variables header file
#include "SoundManager.h"  //sound manager header file

using namespace std;

//making SnakePosition as struct for  accessibility of member variables and methods.
//in this case pos x and pos y
struct SetPosition {
	int x;
	int y;

	
	SetPosition(int positionX, int positionY) {
		x = positionX;
		y = positionY;
	}
};

class MySnake {

public:
	//initialX = starting X position of snake , initialY = starting Y position of snake

	MySnake(int initialX, int initialY, char direction, SDL_Renderer * renderer);
	~MySnake();  //destructure

	//new added
	void newSetPosition(int x, int y);  //set position of snake
	//function to make our snake run at different position on the screen
	void runSnake();
	//sdl texture function in order to convert texture from surface
	SDL_Texture * loadTextureFromSurface(const char * filename);
	//setup the direction of snake when keyboard pressed
	void setSnakeDirection(char direction);
	//our collission detection function to detect collission
	void collisionDetection();
	//renderour snake
	void renderSnake();
	//this funciton return private attribute isAlive
	bool checkIfAlive() { return isAlive; }
	void eatSnakeFood(); //to eat apples on the screen

	SDL_Texture * gameOverTexture;  //pointer to point gameover texture

    //setting up direction  as static for our snake to move at differentdirection

	static const char dirUp = 0;
	static const char dirDown = 1;
	static const char dirRight = 2;
	static const char dirLeft = 3;

	//private attributes
private:
	std::vector<SetPosition *> snakeBody; //making snakebody as vector position
	char direction; //direction
	SDL_Texture * snakeHeadTxt; //snake head texture
	SDL_Texture * snakeBodyTxt; //snake body texture
	SDL_Renderer * renderer; //sdl renderer
	SDL_Texture * foodTexture; //food texture
	SDL_Texture * grassTexture; //grass texture

	bool isAlive;
	SetPosition * snakeFood; 
};