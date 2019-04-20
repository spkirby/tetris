#ifndef SOUND_H
#define SOUND_H

#include "SDL.h"
#include "SDL_mixer.h"

enum SoundId
{
    THUD = 0,
    ROTATE,
    LINE,
    START,
    GAMEOVER,
    NUM_OF_SOUNDS
};

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