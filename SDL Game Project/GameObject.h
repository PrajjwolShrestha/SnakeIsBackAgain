#pragma once
#include <SDL.h>
#include "Vector.h"

class GameObject
{
public:
	SDL_Renderer* renderer;

	Vector pos; //xy position
	Vector velocity; //how fast and where to move from this pos

					 //float x, y;
	GameObject();
	~GameObject();

	//new added
	void setPosition(Vector pos);
	void setVelocity(Vector pos);

	virtual void update(float dt);
	//new added
	virtual void updateMovement(float dt);
	virtual void draw();
};

