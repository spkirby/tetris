#ifndef SOUND_H
#define SOUND_H

#include "SDL.h"
#include "SDL_mixer.h"

enum SoundId
{
    SOUND_THUD = 0,
    SOUND_ROTATE,
    SOUND_LINE,
    SOUND_START,
    SOUND_GAME_OVER,
    NUM_OF_SOUNDS
};

class Sound
{
public:
    Sound();
    ~Sound();
    void play(SoundId soundIndex);
    void stopAll();

protected:
    Mix_Chunk* sounds[NUM_OF_SOUNDS] = { nullptr };

    Mix_Chunk* loadSound(char* filename);
};

#endif