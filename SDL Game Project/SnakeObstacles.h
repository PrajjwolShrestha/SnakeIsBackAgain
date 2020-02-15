#pragma once
#include "GameObject.h"
#include "Animation.h"


class SnakeObstacles : public GameObject
{
public:
	int w, h; //width and hight for obstacles

	SnakeObstacles();
	~SnakeObstacles();

	//override draw function from gameobject
	void draw();
};

