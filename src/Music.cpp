#include "Music.h"

Music::Music(string path)
{
    music =  Mix_LoadMUS(path.c_str());
    if (music == NULL )
        cout<<"Unable to load Music!\n";
}

void Music:: Play(int loop)
{
    Mix_PlayMusic(music,loop);

}

void Music::Pause()
{
    if (Mix_PausedMusic()==0)
        Mix_PauseMusic();
    else
        cout<<"Music is already Paused!\n";
}

void Music:: Resume()
{
    if (Mix_PausedMusic()==1)
        Mix_ResumeMusic();
    else
        cout<<"Music is already playing\n";
}

Music::~Music()
{
    Mix_FreeMusic(music);
}
