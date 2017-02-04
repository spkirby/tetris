#ifndef SOUND_H
#define SOUND_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

class Sound
{
public:
	enum SoundID
	{
		THUD = 0,
		ROTATE,
		LINE,
		START,
		GAMEOVER,
		NUM_OF_SOUNDS
	};

	static void init();
	static void shutdown();
	static Mix_Chunk* loadSound(char* filename);
	static void play(SoundID soundIndex);
	static void stopAll();

protected:
	static Mix_Chunk* sounds[NUM_OF_SOUNDS];

private:
	Sound();
	~Sound();
};

#endif