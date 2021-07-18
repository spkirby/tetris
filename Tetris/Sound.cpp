#include "SDL_mixer.h"
#include "Sound.h"

Sound::Sound()
{
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
    {
        throw Mix_GetError();
    }

    sounds[SOUND_THUD] = loadSound("sound/thud.wav");
    sounds[SOUND_ROTATE] = loadSound("sound/rotate.wav");
    sounds[SOUND_LINE] = loadSound("sound/line.wav");
    sounds[SOUND_START] = loadSound("sound/start.wav");
    sounds[SOUND_GAME_OVER] = loadSound("sound/gameover.wav");
}

Sound::~Sound()
{
    for (int i = 0; i < NUM_OF_SOUNDS; i++)
    {
        if (sounds[i])
        {
            Mix_FreeChunk(sounds[i]);
        }
    }

    Mix_CloseAudio();
    Mix_Quit();
}

Mix_Chunk* Sound::loadSound(char* filename)
{
    return Mix_LoadWAV(filename);
}

void Sound::play(SoundId soundIndex)
{
    if (sounds[soundIndex] != nullptr)
    {
        Mix_PlayChannel(-1, sounds[soundIndex], 0);
    }
}

void Sound::stopAll()
{
    Mix_HaltChannel(-1);
}