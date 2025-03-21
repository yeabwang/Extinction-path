#ifndef MUSIC_H
#define MUSIC_H

#include "Sound.h" 
#include <SDL_mixer.h> 
#include <stdio.h> 

class Music : public Sound {
public:
    Music(const char* path); 
    Music(const Music&) = delete; 
    Music& operator=(const Music&) = delete; 
    void Play(int loop = -1);
    void Pause();
    void Resume();
    virtual ~Music();

private:
    Mix_Music* music;
};

#endif // MUSIC_H