#include "SnakeObstacles.h"



SnakeObstacles::SnakeObstacles()
{

}


SnakeObstacles::~SnakeObstacles()
{
}


void SnakeObstacles::draw()
{
	SDL_Rect rectObstacle = { pos.x,pos.y,w,h };
	//set render draw colour
	SDL_SetRenderDrawColor(renderer, 108, 122, 137, 1);
	//draw the rectangle obstacles for our snake game
	SDL_RenderFillRect(renderer, &rectObstacle);
}
