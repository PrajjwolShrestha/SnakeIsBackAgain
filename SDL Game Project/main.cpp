#include <SDL.h>
#include <SDL_image.h> //sdl rlibrary to load up images which supports lots of image files like png, jpg,etc
#include <string>
#include <iostream>

#include <SDL_ttf.h> //for loading our text fonts
#include <SDL_mixer.h> //for loading  audio and music
#include "ManageSound.h" //sound managing library


using namespace std;

//for our SDL to work, we need main signature instead of void main()
int main(int argc, char **argv)
{

	//initialise SDL and its subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "ERROR: " << SDL_GetError() << endl;
		system("pause"); //pause the system
		return -1; //exit program early
	}
	else
	{
		//successfully initialised
		cout << "SDL initialised!!!" << endl;
	}
	//load text
	if (TTF_Init() != 0)
	{
		//failed!
		cout << "TTF FAILED: " << TTF_GetError() << endl;
		system("pause");
		SDL_Quit();
		return -1;
	}

	//Initialise SDL image
	if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG)))
	{
		//if didn't work, report error
		cout << "SDL IMAGE ERROR: " << IMG_GetError() << endl;
		SDL_Quit(); //cleanup SDL memory
		system("pause");
		return -1; //exits the program early
	}

	//mixer int
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) //frequency, format , channels, chunksize
	{
		//report error
		cout << "Mixer error!!!:  " << Mix_GetError() << endl;
		SDL_Quit();
		system("pause");
		return -1;
		
	}

	//After initialising SDL Image , now we are Creating a SDL Window
	//params: 
	//	window title, x and y pos, width, height, flags for creation
	SDL_Window* window = SDL_CreateWindow("Snake is Back", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1024, 720, SDL_WINDOW_SHOWN);//|SDL_WINDOW_FULLSCREEN

	if (window != NULL) {
		cout << "window created!" << endl;  //SDL_Window created successfully
	}
	else
	{
		//window not created
		cout << "ERROR: " << SDL_GetError() << endl;
		system("pause");
		SDL_Quit(); //cleanup SDL memory
		return -1; //exit the program
	}

	//create renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL) {
		cout << "ERROR: " << SDL_GetError() << endl;  //renderer not created
		system("pause");
		SDL_Quit(); //cleanup SDL memory
		return -1; //exit the program
	}

	//Load up FONT file
	TTF_Font* myFont = TTF_OpenFont("assets/vermin_vibes_1989.ttf", 40);//params: file path, font size
	SDL_Color colourOfText = { 255, 128, 34, 255};
	//create surface(image in ram) using font, colour and text
	SDL_Surface* textSurface = TTF_RenderText_Blended(myFont, "WELCOME TO SNAKE IS BACK GAME!", colourOfText);
	//convert surface to texture
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	//cleanup surface
	SDL_FreeSurface(textSurface);

	//Text destination
	SDL_Rect textDestination;
	textDestination.x = 100;
	textDestination.y = 10;
	//query texture for width and height
	SDL_QueryTexture(textTexture, NULL, NULL, &textDestination.w, &textDestination.h);


	//Load up BackGround Grass for our Snake Game
	SDL_Surface* backGrassSurface = IMG_Load("assets/grass.jpg");  //background grass
	//converting grass surface to texture
	SDL_Texture* backGrassTexture = SDL_CreateTextureFromSurface(renderer, backGrassSurface); 
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


	//load surface images for our Snake Game
	SDL_Surface* snakeMenuSurface = IMG_Load("assets/snakeMenu.png"); //menu for our snake game
	//converting menu surface to texture
	SDL_Texture*  snakeMenuTexture = SDL_CreateTextureFromSurface(renderer, snakeMenuSurface);

	//load head surface images for our Snake Game
	SDL_Surface* snakeHeadSurface = IMG_Load("assets/snakeHead.png"); //head of our snake
    //converting head surface to texture
	SDL_Texture* snakeHeadTexture = SDL_CreateTextureFromSurface(renderer, snakeHeadSurface);

	//load body surface images for our Snake Game
	SDL_Surface* snakeBodySurface = IMG_Load("assets/snakeBody.png"); //body of our snake
	//converting body surface to texture
	SDL_Texture* snakeBodyTexture = SDL_CreateTextureFromSurface(renderer, snakeBodySurface);

	//load gameover surface images for our Snake Game
	SDL_Surface* gameOverSurface = IMG_Load("assets/gameover.png"); //gameover screen of our snake
	//converting gameover surface to texture
	SDL_Texture* gameOverTexture = SDL_CreateTextureFromSurface(renderer, gameOverSurface);

	//load food surface images for our Snake Game
	SDL_Surface* foodSurface = IMG_Load("assets/food.png"); //food  of our snake
	SDL_Texture* foodTexture = SDL_CreateTextureFromSurface(renderer, foodSurface);//converting food surface to texture

	//Free surface
	SDL_FreeSurface(backGrassSurface);	//Free surface for grass
	SDL_FreeSurface(snakeMenuSurface);	//Free surface for menu
	SDL_FreeSurface(snakeHeadSurface);	//Free surface of head
	SDL_FreeSurface(snakeBodySurface);	//Free surface of body
	SDL_FreeSurface(gameOverSurface);	//Free surface for gameover
	SDL_FreeSurface(foodSurface);	//Free surface for food



	
	//drawing destination rect for our menu
	SDL_Rect gameMenuDestRect;
	SDL_QueryTexture(snakeHeadTexture, NULL, NULL, &gameMenuDestRect.w, &gameMenuDestRect.h);
	gameMenuDestRect.x = 300;
	gameMenuDestRect.y = 200;
	gameMenuDestRect.w = 500;
	gameMenuDestRect.h = 500;

	//drawing destination rect for our snakeHead
	SDL_Rect snakeHeadDest;
	SDL_QueryTexture(snakeHeadTexture, NULL, NULL, &snakeHeadDest.w, &snakeHeadDest.h);
	snakeHeadDest.x = 300;
	snakeHeadDest.y = 100;
	snakeHeadDest.w = snakeHeadDest.w;
	snakeHeadDest.h = snakeHeadDest.h;

	//drawing destination rect for food
	SDL_Rect foodDest;
	SDL_QueryTexture(foodTexture, NULL, NULL, &foodDest.w, &foodDest.h);
	foodDest.x = 500;
	foodDest.y = 100;
	foodDest.w = 40;
	foodDest.h = 40;


	//drawing destination rect for gameOver
	SDL_Rect gameOverDest;
	SDL_QueryTexture(gameOverTexture, NULL, NULL, &gameOverDest.w, &gameOverDest.h);
	gameOverDest.x = 600;
	gameOverDest.y = 50;
	gameOverDest.w = gameOverDest.w ;
	gameOverDest.h = gameOverDest.h;

	Uint32 lastUpdate = SDL_GetTicks();

	bool loop = true;

	//Game loop

	while (loop)
	{
		//difference of current time minus last update time
		Uint32 timeDiff = SDL_GetTicks() - lastUpdate;

		float DT = timeDiff / 1000.0;
		lastUpdate = SDL_GetTicks();

		//load up our music
		Mix_Music* music = Mix_LoadMUS("assets/music.ogg");
		if (music == NULL)
		{
			//report error
			cout << "Music failed to load: " << Mix_GetError() << endl;
			system("pause");
			SDL_Quit();
			return -1;

		}
		//play music
		Mix_PlayMusic(music, -1);


		//Load up sound effects
		/*ManageSound::manageSound.loadSound("music", "assets/music.ogg");
		ManageSound::manageSound.playSound("music");*/

		//explode sound loaded 
		ManageSound::manageSound.loadSound("explode", "assets/effect.wav");
		//powerup sound loaded 
		//TODO: play when our snake eats food
		ManageSound::manageSound.loadSound("powerup", "assets/Powerup.wav");

		//INPUT HANDLING
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			//check if user clicked close on window
			if (e.type == SDL_QUIT) {
				loop = false;
			}
			//check if user pressed a button
			if (e.type == SDL_KEYDOWN) {
				//see if ESC key pressed
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					loop = false;
				}
			}
		}

		//set render draw colour with RGBA value (values between 0-255)
		SDL_SetRenderDrawColor(renderer, 188, 0, 168, 188);
		//clear the screen with current draw colour
		SDL_RenderClear(renderer);
		//change render draw colour
		SDL_SetRenderDrawColor(renderer, 0, 228, 255, 188);
		//make a rectangle to draw to the screen (x,y,w,h)
		SDL_Rect rect = { 100, 50, 300, 240 };
		//draw rect to screen with current draw colour
		SDL_RenderFillRect(renderer, &rect);

		//draw grass image
		SDL_RenderCopy(renderer, backGrassTexture, &grassRect, &grassDestinationRect);
		//draw menu
		SDL_RenderCopy(renderer, snakeMenuTexture,NULL, &gameMenuDestRect);
		//draw snake head
		SDL_RenderCopy(renderer, snakeHeadTexture, NULL, &snakeHeadDest);
		//draw gameover
		SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverDest);
		//draw food
		SDL_RenderCopy(renderer, foodTexture, NULL, &foodDest);

		//swap the buffers, show our current frame we've been drawing
		SDL_RenderPresent(renderer);



		//drawing text on top of everything else
		SDL_RenderCopy(renderer, textTexture, NULL, &textDestination);
		//swap the buffers, show our current frame we've been drawing
		SDL_RenderPresent(renderer);

		

		system("pause"); //for checking game end sound

		//play powerup sound for our gameover part later
		ManageSound::manageSound.playSound("powerup");

		//sdl_getTicks returns number of milliseconds since start of program running
		if (SDL_GetTicks() > 10000)
		{
			loop = false;
			SDL_Delay(5000);

			ManageSound::manageSound.playSound("powerup");

		}
	}

	// wait for 5 seconds(5000ms)
	//SDL_Delay(5000);

	//CLEANUP
	TTF_CloseFont(myFont);
	SDL_DestroyTexture(textTexture);
	SDL_DestroyTexture(backGrassTexture);
	SDL_DestroyTexture(snakeHeadTexture);
	SDL_DestroyTexture(foodTexture);
	SDL_DestroyTexture(snakeBodyTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	system("pause");
	return 0;
}