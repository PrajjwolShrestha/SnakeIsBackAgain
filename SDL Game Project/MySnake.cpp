#include "MySnake.h"


MySnake::MySnake(int tmpX, int tmpY, char snakeDirection, SDL_Renderer* snakeRenderer) {
	direction = snakeDirection;
	renderer = snakeRenderer;
	isAlive = true;
	
	//setup positions and load up snake textures
	snakeFood = new SetPosition(0, 0);
	do {
		//rand genreates random math number
		snakeFood->x = rand() % SnakeBlock; //place food  at random 'X'pos of screen when game starts
		snakeFood->y = rand() % SnakeBlock; //place food at random 'Y' pos
	} while (snakeFood->x != tmpX && snakeFood->y != tmpY); //setting up temporary or starting value os X and Y
	newSetPosition(tmpX, tmpY);


	//load the texture of snake parts
	//load food texture from surface
	foodTexture = loadTextureFromSurface("assets/food.png");
	//load head texture  from surface
	snakeHeadTxt = loadTextureFromSurface("assets/head2.png");
	//load body texture from surface
	snakeBodyTxt = loadTextureFromSurface("assets/body.png");
	//load gameover texture from surface
	gameOverTexture = loadTextureFromSurface("assets/gameover.png");
}


//destructure
MySnake::~MySnake() {
	//use it for deleting the body of snake when game is over
	for (int bodyPart = 0; bodyPart < snakeBody.size(); bodyPart++)
		delete snakeBody[bodyPart];
}

//set up new position of the snake at X and Y
void MySnake::newSetPosition(int posX, int posY) {
	SetPosition * newPosition = new SetPosition(posX, posY);
	snakeBody.push_back(newPosition);  //added the bodyPosition for the snake
}

void MySnake::runSnake() {
	//run our snake when it is alive
	if (!isAlive) return;
	//setting up new position
	int xDirection, yDirection;
	//switch case for different cases
	//change direction when we move snake
	switch (direction) {
	case MySnake::dirUp: //when my snake direction is up
		xDirection = 0;
		yDirection = -1;
		break;
	case MySnake::dirDown: //when my snake direction is down
		xDirection = 0;
		yDirection = 1;
		break;
	case MySnake::dirRight: //when my snake direction is right
		xDirection = 1;
		yDirection = 0;
		break;
	case MySnake::dirLeft: //when my snake direction is left
		xDirection = -1;
		yDirection = 0;
		break;
	default:
		break;
	}
	//delete snake body from back when game is over
	//add snake body from the front just behind the head when we eat food

	for (int bodyOfSnake = snakeBody.size() - 1; bodyOfSnake > 0; bodyOfSnake--) {
		snakeBody[bodyOfSnake]->x = snakeBody[bodyOfSnake - 1]->x;
		snakeBody[bodyOfSnake]->y = snakeBody[bodyOfSnake - 1]->y;
	}
	SetPosition * snakeHead = *(snakeBody.begin());
	snakeHead->x += xDirection;
	snakeHead->y += yDirection;
}

//load snake textures
SDL_Texture* MySnake::loadTextureFromSurface(const char* filename) {
	SDL_Surface * snakeSurfaceLoad = IMG_Load(filename);
	//set colour key( this colour goes fully transparent)
	//params: surface, set or unset(1/0), uint for colour (using mapRGB to find index of this colour in image)
	//SDL_SetColorKey(loadSurface, 1, SDL_MapRGB(loadSurface->format, 128, 128, 255));

	if (!snakeSurfaceLoad)
    cout << "Image failed to load!!! " << filename << ": " << IMG_GetError() << endl;
	SDL_Texture * createTextureFromSurface = SDL_CreateTextureFromSurface(renderer, snakeSurfaceLoad);
	SDL_FreeSurface(snakeSurfaceLoad);  //cleanup memory
	return createTextureFromSurface;
}

//set the direction of our snake up, down, left, and right
void MySnake::setSnakeDirection(char setDirection) {
	switch (direction) {
	case MySnake::dirUp:
		//when facing up we cant' go down
		if (setDirection == MySnake::dirDown) return; 
		if (snakeBody.size() > 1 && snakeBody[0]->y == snakeBody[1]->y) return;
		break;
	case MySnake::dirDown:
		//when facing down we can't go up
		if (setDirection == MySnake::dirUp) return;
		if (snakeBody.size() > 1 && snakeBody[0]->y == snakeBody[1]->y) return;
		break;
	case MySnake::dirRight:
		//when facing right we can't face left
		if (setDirection == MySnake::dirLeft) return;
		if (snakeBody.size() > 1 && snakeBody[0]->x == snakeBody[1]->x) return;
		break;
	case MySnake::dirLeft:
		//when facing left we can't face right
		if (setDirection == MySnake::dirRight) return;
		if (snakeBody.size() > 1 && snakeBody[0]->x == snakeBody[1]->x) return;
		break;
	}
	direction = setDirection;
}

//LOSE CASE SCENARIO OF GAME

//function to check the collission of our snake
void MySnake::collisionDetection() {
	
	SetPosition * snakeHead = snakeBody[0];
	//if position of snake's is greater than our screen Size
	//that means snake collide with the end of screen
	//loss case scenario for our game
	if (snakeHead->x < 0 || snakeHead->x > SnakeBlock - 1 || snakeHead->y < 0 || snakeHead->y > SnakeBlock - 1) {
		isAlive = false;//gameover
		return;
	}
	for (int bodyParts = 1; bodyParts < snakeBody.size(); bodyParts++) {
		//if our snake head collides with any part of body, gameover
		//losscase scenario of game
		if (snakeHead->x == snakeBody[bodyParts]->x && snakeHead->y == snakeBody[bodyParts]->y) {
			isAlive = false;
			break;
		}
	}
}

//RENDER THE FOOD,BODY, HEAD TEXTURE OF SNAKE 

void MySnake::renderSnake() {
	SDL_Rect sdl_rect;
	sdl_rect.w = sdl_rect.h = ConstantSize; //making all equal (square) value:32
	sdl_rect.x = snakeFood->x * ConstantSize ; //set x value of rect
	sdl_rect.y = snakeFood->y * ConstantSize; //set y value of rect
	//copy foodTexture to render
	SDL_RenderCopy(renderer, foodTexture, NULL, &sdl_rect); 
	//FOR RENDERING SNAKE BODY
	sdl_rect.x = snakeBody[0]->x * ConstantSize;  //x value
	sdl_rect.y = snakeBody[0]->y * ConstantSize; //y value
	 //now copy head texture to render
	 //param:renderer, texture, sourcerect, destinationrect, angle,flip
	SDL_RenderCopyEx(renderer, snakeHeadTxt, NULL, &sdl_rect,
		(direction == MySnake::dirLeft || direction == MySnake::dirRight) ? 90.0 : 0.0,
		NULL, SDL_FLIP_NONE);
	//for body texture
	for (int renderBody = 1; renderBody < snakeBody.size(); renderBody++) {
		sdl_rect.x = snakeBody[renderBody]->x * ConstantSize;
		sdl_rect.y = snakeBody[renderBody]->y * ConstantSize;
		SDL_RenderCopy(renderer, snakeBodyTxt, NULL, &sdl_rect);
	}


}



void MySnake::eatSnakeFood() {
	//if snake eats the food add food to snake body below head region
	//we subtracted from body because we want to add segment below the head not above
	if (snakeBody[0]->x == snakeFood->x && snakeBody[0]->y == snakeFood->y)
		newSetPosition(snakeBody[snakeBody.size() - 1]->x, snakeBody[snakeBody.size() - 1]->y);
	else return; 

	//AUTO::specifies that 
	//type of variable that is being declared 
	//will automatically be deducted from its initializer.
	//In  functions, if return type is auto
	//will be evaluated by return type expression at runtime.
	auto collisionHappened = [&]() {
		for (auto tmpValue : snakeBody) {
			if (snakeFood->x == tmpValue->x && snakeFood->y == tmpValue->y)
				return true;
			//load and play sound when we eat snake foood
			SoundManager::sm.loadSound("bite", "assets/bite.wav"); //load wav sound
			SoundManager::sm.playSound("bite"); //play the sound 


		}
		return false;
	};

	do {
		snakeFood->x = rand() % SnakeBlock; //set at random pos
		snakeFood->y = rand() % SnakeBlock; //set Y value at random pos
	} while (collisionHappened());
}

