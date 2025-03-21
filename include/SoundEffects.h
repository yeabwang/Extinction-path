#ifndef SOUNDEFFECTS_H
#define SOUNDEFFECTS_H

#include "Sound.h" 
#include <SDL_mixer.h> 
#include <stdio.h> 

class SoundEffects : public Sound {
public:
    SoundEffects(const char* path); 
    SoundEffects(const SoundEffects&) = delete; 
    SoundEffects& operator=(const SoundEffects&) = delete; 
    void Play(int loop = 0);
    void Pause();
    void Resume();
    virtual ~SoundEffects();

private:
    Mix_Chunk* chunk;
};

#endif // SOUNDEFFECTS_H