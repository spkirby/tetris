#include "SDL_mixer.h"
#include "Sound.h"

Sound::Sound()
{
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) != 0)
    {
        throw Mix_GetError();
    }

    sounds[(int)SoundId::Thud] = loadSound("sound/thud.wav");
    sounds[(int)SoundId::Rotate] = loadSound("sound/rotate.wav");
    sounds[(int)SoundId::LineComplete] = loadSound("sound/line.wav");
    sounds[(int)SoundId::StartGame] = loadSound("sound/start.wav");
    sounds[(int)SoundId::GameOver] = loadSound("sound/gameover.wav");
}

Sound::~Sound()
{
    for (int i = 0; i < (int)SoundId::Count; i++)
    {
        if (sounds[i])
        {
            Mix_FreeChunk(sounds[i]);
            sounds[i] = nullptr;
        }
    }

    Mix_CloseAudio();
    Mix_Quit();
}

Mix_Chunk* Sound::loadSound(const char* filename)
{
    return Mix_LoadWAV(filename);
}

void Sound::play(SoundId soundId)
{
    if (sounds[(int)soundId] != nullptr)
    {
        Mix_PlayChannel(-1, sounds[(int)soundId], 0);
    }
}

void Sound::stopAll()
{
    Mix_HaltChannel(-1);
}