#ifndef MUSIC_H
#define MUSIC_H
#include "Sound.h"
#include "SDL_mixer.h"

class Music: public Sound
{
    public:
        Music(string path);
        Music(const& Music) = delete;///deleted this because we won't make any copy
        Music& operator=(const& Music) = delete;///deleted this because we won't make any assignment
        Music()=delete;///deleted this because we will always use overloaded constructor
        void Play(int loop=-1);
        void Pause();
        void Resume();
        virtual ~Music();
    protected:

    private:
        Mix_Music* music;
};

#endif // MUSIC_H
