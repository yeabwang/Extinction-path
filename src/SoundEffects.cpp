#include "SoundEffects.h"

SoundEffects::SoundEffects(string path)
{
    chunk = Mix_LoadWAV(path.c_str());
    if (!chunk)
        cout<<"Unable to load effect\n";
}

void SoundEffects::Play(int loop)
{
    Mix_PlayChannel(-1,chunk,loop);
}
void SoundEffects::Pause()
{

}
void SoundEffects::Resume(){}

SoundEffects::~SoundEffects()
{
    Mix_FreeChunk(chunk);
}
