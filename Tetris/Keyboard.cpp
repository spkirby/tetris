#include "Keyboard.h"
#include "SDL.h"

Keyboard::Keyboard() :
    keystate(SDL_GetKeyboardState(&keystateLength))
{
}

bool Keyboard::isKeyDown(SDL_Keycode keycode)
{
    SDL_Scancode scancode = SDL_GetScancodeFromKey(keycode);

    return scancode > SDL_SCANCODE_UNKNOWN
        && scancode < keystateLength
        && keystate[scancode] != 0;
}

bool Keyboard::isAnyKeyDown()
{
    for (int i = 0; i <= keystateLength; i++)
    {
        if (keystate[i] != 0)
        {
            return true;
        }
    }

    return false;
}
