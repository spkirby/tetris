#include <ctime>
#include <cstdlib>
#include <cstdio>
#include "SDL.h"
#include "SDL_mixer.h"
#include "Game.h"
#include "Graphics.h"
#include "Sound.h"

void startGame()
{
    Graphics graphics;
    Sound sound;
    Game theGame(graphics, sound);

    theGame.start();
}

int main(int argc, char *argv[])
{
    try
    {
        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
            throw SDL_GetError();

        srand((unsigned int)time(NULL));
        startGame();
    }
    catch(const char* ex)
    {
        fprintf(stderr, "An unrecoverable error occurred. %s\n", ex);
    }

    SDL_Quit();

    return 0;
}
