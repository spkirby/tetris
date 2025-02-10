#pragma once
#include "SDL.h"
#include "SDL_mixer.h"

enum class SoundId
{
    Thud,
    Rotate,
    LineComplete,
    StartGame,
    GameOver,
    Count // Count of SoundId entries
};

class Sound
{
public:
    Sound();
    ~Sound();
    void play(SoundId soundId);
    void stopAll();

protected:
    Mix_Chunk* sounds[(int)SoundId::Count] = { nullptr };

    Mix_Chunk* loadSound(const char* filename);
};
