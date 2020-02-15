#include "SnakeGameFunctions.h"
#include "SoundManager.h" //sound managing library
#include <SDL_ttf.h> //for loading our text fonts
#include <SDL_mixer.h> //for loading  audio and music
#include <SDL_image.h> //sdl rlibrary to load up images which supports lots of image files like png, jpg,etc
#include <string>  //library to work with strings
#include "SnakeObstacles.h" //gameplay elements header file to work with obtacles
#include <list> //in order to work with list of objects


//pointers pointing null
SnakeGameFunctions * snakeGameFunction = nullptr;

using namespace std;

// need old 'main' signature, not void main()  for working SDL
int main(int argc, char * argv[]) {
	//game introduction and hints
	cout << "WELCOME TO SNAKE IS BACK GAME DESIGNED BY PRAJJWOL SAMA SHRESTHA! " << endl;
	cout << "................................................................. " << endl << endl;
	cout << "Game Instruction:" << endl;
	cout << "To play this game, Use following buttons to move snake at different direction: " << endl;
	cout << "Up arrow = Upward direction" << endl;
	cout << "Down arrow = Downward direction" << endl;
	cout << "Left arrow = Left Direction" << endl;
	cout << "Right arrow = Right Direction" << endl;
	cout << endl;
	cout << "LOSE CASE SNENARIO: DON'T RUNT THE SNAKE TO THE WALL OR IT'S OWN BODY." << endl;
	cout << "TRY TO EAT AS MUCH APPLE AS YOU CAN. " << endl;
	cout << "THE MORE YOU EAT, MORE WILL BE THE HIGHSCORE WHICH IS THE MAIN THEME OF THIS GAME. " << endl;
	cout << ".................................................................... " << endl;
	cout << "GOOD LUCK! " << endl;


	system("pause"); //pause the screen

	//initialise SDL and its subsystems
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "ERROR: " << SDL_GetError() << endl;
		system("pause");
		return -1;  //exits program 
	}
	else
	{
		//success
		cout << "SDL initialised!!" << endl;
	}

	//Initialise SDL image
	if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG)))
	{
		//if image didn't work, report back the error message
		cout << "SDL IMAGE ERROR: " << IMG_GetError() << endl;
		SDL_Quit();
		system("pause");
		return -1;
	}
	//video initialisation
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL Video Initialisation failed: " << SDL_GetError() << endl;
		return -1;
	}


	//for fonts
	if (TTF_Init() != 0)
	{
		//TTF_INit failed
		cout << "TTF FAILED: " << TTF_GetError() << endl;
		system("pause");
		SDL_Quit();
		return -1;
	}

	//mixer int
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) //frequency, format , channels, chunksize
	{
		//report error
		cout << "Mixer error!!!:  " << Mix_GetError() << endl;
		system("pause");
		SDL_Quit();
		return -1;
	}


	

	//set random number series seed value (changes which set of random numbers are returned from rand)
	srand(time(NULL));  //time(null) gives milliseconds since the start of this year, so be different each game run

	/*const int noOfFrame = 5;
	const int runClipRate = 1000 / noOfFrame;*/

	runClipRate; //constant integer 


	Uint32 lastUpdate; //lastUpdate
	int timeDifference; //timedifference

	snakeGameFunction = new SnakeGameFunctions();  //making new object
	//initialise everything and start the game
	//includes initialisation of window, renderer, and ttf fonts
	snakeGameFunction->gameInit("Snake is Back", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, ScreenSize, ScreenSize, false);


	//run the game 
	//handle different function while game is running and when game finishes clean 
	//up everything and close the game
	//clean everything for saving memory
	while (snakeGameFunction->gameIsRunning()) {

		lastUpdate = SDL_GetTicks();

		
		//made functions to handle keyboard rather than making a separate class
		snakeGameFunction->keyboardHandler();  //handle the keyboard control for our snake
		snakeGameFunction->updateEverything();  //updates everything and checks if game is still running or not
		snakeGameFunction->render(); //render our snake
		//similar as using deltatime
		//this make our game to run smoothly in all types of computer
		//no worry if our computer is slow or fast
		timeDifference = SDL_GetTicks() - lastUpdate; //gets current time difference so that our game is up to date and does not lag
		if (runClipRate > timeDifference)
			SDL_Delay(runClipRate - timeDifference); //delay the sdl 
	}
	snakeGameFunction->freeMemory(); //cleans memory RAM
	return 0;
}