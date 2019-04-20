#include "SDL_mixer.h"
#include "Sound.h"

Mix_Chunk* sounds[NUM_OF_SOUNDS] = { nullptr };

Sound::Sound()
{
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
        throw Mix_GetError();

    sounds[THUD] = loadSound("sound/thud.wav");
    sounds[ROTATE] = loadSound("sound/rotate.wav");
    sounds[LINE] = loadSound("sound/line.wav");
    sounds[START] = loadSound("sound/start.wav");
    sounds[GAMEOVER] = loadSound("sound/gameover.wav");
}

Sound::~Sound()
{
    for(int i=0; i < NUM_OF_SOUNDS; i++)
    {
        if(sounds[i])
            Mix_FreeChunk(sounds[i]);
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
    if (sounds[soundIndex] != NULL)
    {
        Mix_PlayChannel(-1, sounds[soundIndex], 0);
    }
}

void Sound::stopAll()
{
    Mix_HaltChannel(-1);
}