#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <iostream>


using namespace std;


class SnakeGameFunctions
{
public:
	SnakeGameFunctions();
	~SnakeGameFunctions();

	void render();
	void clean();

private:
	SDL_Window* snakeWindow;
	SDL_Renderer* renderer;

};

