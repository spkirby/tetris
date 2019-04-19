#include <ctime>
#include <cstdlib>
#include <cstdio>
#include "SDL.h"
#include "SDL_mixer.h"
#include "Game.h"
#include "Graphics.h"
#include "Sound.h"

int main(int argc, char *argv[])
{
	try
	{
		if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
			throw SDL_GetError();

		Graphics::init();
		Sound::init();

		srand((unsigned int)time(NULL));

		Game theGame;
		theGame.start();
	}
	catch(const char* ex)
	{
		fprintf(stderr, "An unrecoverable error occured. %s\n", ex);
	}

	Sound::shutdown();
	Graphics::shutdown();
	SDL_Quit();

	return 0;
}
