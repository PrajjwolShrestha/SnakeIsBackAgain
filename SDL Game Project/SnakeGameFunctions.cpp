#include "SnakeGameFunctions.h"



using namespace std;


//making everything as nullptr initially
SnakeGameFunctions::SnakeGameFunctions() {
	gameWindow = nullptr;
	snakeRenderer = nullptr;
	gameRunning = false;
	mySnake = nullptr;
	gameObject = nullptr;
}

//destructure for deleting snake
SnakeGameFunctions::~SnakeGameFunctions() {
	delete mySnake;
}

//function that initialises everything
//init window,renderer,ttf,music...
void SnakeGameFunctions::gameInit(const char* gameTitle, int xPosition, int yPosition, int width, int height, bool maximised) {

	//params:
	//window title, x and y pos, width, height, flags for creation
	SDL_Window* window = SDL_CreateWindow(gameTitle, xPosition, yPosition, width, height, maximised == true ? SDL_WINDOW_MAXIMIZED : NULL);

	if (window != NULL)
	{
		//window created successfully
		cout << "Window Created!!! " << endl;
	}
	else
	{
		//failed..report error
		cout << "ERROR: " << SDL_GetError() << endl;
		system("pause");
		SDL_Quit(); //cleanup SDL memory 
		return; //exit the program
	}

	//Create renderer
	snakeRenderer = SDL_CreateRenderer(window, -1, NULL);
	if (snakeRenderer == NULL) {
		//failed to create renderer..report error
		cout << "ERROR:  " << SDL_GetError() << endl;
		system("pause");
		SDL_Quit(); //cleanup the SDL memory
		return; //exit the program
	}




	//Load up FONT file
	TTF_Font* myFont = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 40);//params: file path, font size
	SDL_Color colourOfText = { 255, 128, 34, 255 };
	//create surface(image in ram) using font, colour and text
	SDL_Surface* textSurface = TTF_RenderText_Blended(myFont, "WELCOME TO SNAKE IS BACK GAME!", colourOfText);
	//convert surface to texture
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(snakeRenderer, textSurface);
	//cleanup surface
	SDL_FreeSurface(textSurface);

	//ANOTHER TEXT ON THE SCREEN
	SDL_Surface* textSurface1 = TTF_RenderText_Blended(myFont, "Eat as many apples as you can.", colourOfText);
	//convert surface to texture
	SDL_Texture* textTexture1 = SDL_CreateTextureFromSurface(snakeRenderer, textSurface1);
	//cleanup surface
	SDL_FreeSurface(textSurface1);

	//Text destination
	SDL_Rect textDestination;
	textDestination.x = 100;
	textDestination.y = 300;
	//query texture for width and height
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination.w, &textDestination.h);

	//Text destination for texttexture1
	SDL_Rect textDestination1;
	textDestination1.x = 80;
	textDestination1.y = 400;
	//query texture for width and height
	SDL_QueryTexture(textTexture1, NULL, NULL, &textDestination1.w, &textDestination1.h);


	//Load up BackGround Grass for our Snake Game
	SDL_Surface* backGrassSurface = IMG_Load("assets/grass.jpg");  //background grass
																   //converting grass surface to texture
	SDL_Texture* backGrassTexture = SDL_CreateTextureFromSurface(snakeRenderer, backGrassSurface);
	//make region for our grass to be drawn
	SDL_Rect grassRect;
	//store w and h of backGrassTexture into source grassRect
	SDL_QueryTexture(backGrassTexture, NULL, NULL, &grassRect.w, &grassRect.h);
	grassRect.x = 0;
	grassRect.y = 0;
	grassRect.w = 1280;
	grassRect.h = 720;
	//drawing destination rect
	SDL_Rect grassDestinationRect;
	grassDestinationRect.x = 0;
	grassDestinationRect.y = 0;
	grassDestinationRect.w = grassRect.w;
	grassDestinationRect.h = grassRect.h;


	SDL_FreeSurface(backGrassSurface);	//Free surface for grass


										//SDL_RendererDraw
										//set render draw color with RGBA value (values between 0-255)

										//draw grass image
	SDL_RenderCopy(snakeRenderer, backGrassTexture, &grassRect, &grassDestinationRect);
	//green colour snake game background
	SDL_SetRenderDrawColor(snakeRenderer, 33, 130, 76, 3);
	gameRunning = true; //boolen.. make our game running as true at this point after initialising everything

	//setup snake width and height and position
	//render it
	mySnake = new MySnake(SnakeBlock / 2, SnakeBlock / 2, rand() % 4, snakeRenderer);



	//load up our music
	Mix_Music* music = Mix_LoadMUS("assets/jackbox.wav");
	if (music == NULL)
	{
		//report error
		cout << "Music failed to load: " << Mix_GetError() << endl;
		system("pause");
		SDL_Quit();
		return;

	}


	//play music
	Mix_PlayMusic(music, -1);

	//drawing text on top of everything else
	SDL_RenderCopy(snakeRenderer, textTexture, NULL, &textDestination);

	//drawing text on top of everything else
	SDL_RenderCopy(snakeRenderer, textTexture1, NULL, &textDestination1);

	//swap the buffers, show our current frame we've been drawing
	SDL_RenderPresent(snakeRenderer);

	SDL_Delay(5000);
	


	//Load up sound effects
	SoundManager::sm.loadSound("explode", "assets/effect.wav");
	SoundManager::sm.loadSound("powerup", "assets/Powerup.wav");



}


//our main snake keyboard handling from here
void SnakeGameFunctions::keyboardHandler() {
	SDL_Event ev;
	while (SDL_PollEvent(&ev)) {

		//when keyboard button is pressed
		if (ev.type == SDL_KEYDOWN) {
			switch (ev.key.keysym.sym) {
			case SDLK_UP: //up arrow key pressed
				mySnake->setSnakeDirection(MySnake::dirUp); //move snake up
				break;
			case SDLK_DOWN: //down arrow key presses
				mySnake->setSnakeDirection(MySnake::dirDown); //move sanke down
				break;
			case SDLK_LEFT: //left arrow key pressed
				mySnake->setSnakeDirection(MySnake::dirLeft); //move snake left
				break;
			case SDLK_RIGHT: //right arrow key pressed
				mySnake->setSnakeDirection(MySnake::dirRight); //move snake right
				break;
			case SDLK_RETURN:  //close the window
				if (!mySnake->checkIfAlive()) gameRunning = false; //game over 
				break;
			/*case SDLK_SPACE:
				mySnake->checkIfAlive();*/
			default:
				break;
			}
		}
		// user clicked close button on the window
		else if (ev.type == SDL_QUIT) gameRunning = false;
	}
}

//this function checks if snake is alive and updates every thing to run the snake
void SnakeGameFunctions::updateEverything() {
	//if snake is slive, check collision,eat food and run our snake until collision happens 
	if (mySnake->checkIfAlive()) {
		mySnake->collisionDetection();
		mySnake->eatSnakeFood();
		mySnake->runSnake();
	}
}

//render the snake in the screen if snake is alive
void SnakeGameFunctions::render() {
	SDL_RenderClear(snakeRenderer);
	mySnake->renderSnake();
	if (!mySnake->checkIfAlive()) {
		SoundManager::sm.playSound("powerup"); //play powerup music
		SDL_Rect s_rect;
		s_rect.w = 150;// Image width
		s_rect.h = 105;// Image height
		s_rect.x = (ScreenSize - s_rect.w) / 2; //X pos
		s_rect.y = (ScreenSize - s_rect.h) / 2; //Y pos
		SDL_RenderCopy(snakeRenderer, mySnake->gameOverTexture, NULL, &s_rect);
	}
	SDL_RenderPresent(snakeRenderer);  //render the snake
	

}


//cleans up memory
//memory management
void SnakeGameFunctions::freeMemory() {
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(snakeRenderer);
	SDL_Quit(); //quit sdl
}






