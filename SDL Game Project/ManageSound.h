#pragma once
#include <SDL_mixer.h> //library to deal with audio
#include <string>
#include <list> //for our list of audio and music

using namespace std;

//new datatype made up of a  sound and a look up name
struct SoundList {
	Mix_Chunk* soundChunk;
	string soundName;
};

class ManageSound
{
	list<SoundList> soundList;

public:
	ManageSound();
	~ManageSound();

	void loadSound(string soundName, string file);
	void playSound(string soundName);

	//singleton pattern
	static ManageSound manageSound;
};

