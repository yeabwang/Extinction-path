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
    void Play(int loop = 0) override;
    void Pause() override;
    void Resume() override;
    bool isValid() const { return chunk != nullptr; } // Added validity check
    virtual ~SoundEffects();

private:
    Mix_Chunk* chunk;
};

#endif // SOUNDEFFECTS_H