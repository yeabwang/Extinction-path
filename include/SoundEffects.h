#ifndef SOUNDEFFECTS_H
#define SOUNDEFFECTS_H
#include "iostream"
#include "Sound.h"
#include "SDL_Mixer.h"
using namespace std;

class SoundEffects : public Sound
{
    public:
        SoundEffects(string path);
        SoundEffects(const& Music) = delete;///deleted this because we won't make any copy
        SoundEffects& operator=(const& SoundEffects) = delete;///deleted this because we won't make any assignment
        Music()=delete;///deleted this because we will always use overloaded constructor
        void Play(int loop=0);
        void Pause();
        void Resume();
        virtual ~SoundEffects();
    private:
        Mix_Chunk* chunk;
};

#endif // SOUNDEFFECTS_H
