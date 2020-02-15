#include "SoundManager.h"



SoundManager::SoundManager()
{
}


SoundManager::~SoundManager()
{
	//destroys the sound effects
	for (SoundListing soundlisting : sounds) {
		Mix_FreeChunk(soundlisting.sound); //destroys the sound from the list 
	}
}

void SoundManager::loadSound(string name, string file)
{
	SoundListing soundlisting;
	soundlisting.name = name;
	soundlisting.sound = Mix_LoadWAV(file.c_str());

	//add our soundlisting to our list of sounds
	sounds.push_back(soundlisting);
}

void SoundManager::playSound(string name)
{
	//loop sounds through the soundlisting
	for (SoundListing soundlisting : sounds)
	{
		//check if the name matches the list
		if (soundlisting.name == name)
		{
			//channel, soundfile to play and loops
			Mix_PlayChannel(-1, soundlisting.sound, 0);
			break;  //exit the loop
		}
	}
}

//initialise static sound manager so we can access it anytime, anywhere
SoundManager SoundManager::sm;