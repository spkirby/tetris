#ifndef SOUND_H
#define SOUND_H

#include "enums.h"
#include "SDL.h"
#include "SDL_mixer.h"

class Sound
{
public:
    Sound();
    ~Sound();

    Mix_Chunk* loadSound(char* filename);
    void play(SoundId soundIndex);
    void stopAll();

protected:
    Mix_Chunk* sounds[NUM_OF_SOUNDS];
};

#endif