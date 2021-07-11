#pragma once
#include "SDL.h"

class Keyboard
{
public:
    Keyboard();
    bool isKeyDown(SDL_Keycode keycode);
    bool isAnyKeyDown();

protected:
    const Uint8* keystate;
    int keystateLength;
};

