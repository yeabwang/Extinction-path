#ifndef SOUND_H
#define SOUND_H
#include "SDL.h"
#include "SDL_mixer.h"
#include "iostream"

using namespace std;

class Sound
{
    public:
        virtual void Play(int loop=-1)=0;
        virtual void Pause()=0;
        virtual void Resume()=0;
        virtual ~Sound(){}
};

#endif // SOUND_H
