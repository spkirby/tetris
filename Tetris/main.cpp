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
    Game game(graphics, sound);

    game.start();
}

int main(int argc, char *argv[])
{
    try
    {
        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
            throw SDL_GetError();

        srand((unsigned int)time(nullptr));
        startGame();
    }
    catch(const char* ex)
    {
        fprintf(stderr, "An unrecoverable error occurred. %s\n", ex);
    }

    SDL_Quit();

    return 0;
}
