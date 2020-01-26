#include "ManageSound.h"



ManageSound::ManageSound()
{
	//destroys the sound effects
	for (SoundList soundLists : soundList) {
		Mix_FreeChunk(soundLists.soundChunk); //destroys the sound from the list 
	}
}


ManageSound::~ManageSound()
{
}

void ManageSound::loadSound(string soundName, string file)
{
	SoundList soundLists;
	soundLists.soundName = soundName;
	soundLists.soundChunk = Mix_LoadWAV(file.c_str());

	//add our soundlisting to our list of sounds
	soundList.push_back(soundLists);
}

void ManageSound::playSound(string soundName)
{
	//loop sounds through the soundlisting
	for (SoundList soundLists : soundList)
	{
		//check if the name matches the list
		if (soundLists.soundName == soundName)
		{
			//channel, soundfile to play and loops
			Mix_PlayChannel(-1, soundLists.soundChunk, 0);
			break;  //exit the loop
		}
	}
}

//initialise static sound manager so we can access it anytime, anywhere
ManageSound ManageSound::manageSound;