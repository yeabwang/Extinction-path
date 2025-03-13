#include "Music.h"

Music::Music(const char* path) {
    music = Mix_LoadMUS(path);
    if (music == NULL) {
        printf("Unable to load Music: %s\n", Mix_GetError());
    }
}

void Music::Play(int loop) {
    Mix_PlayMusic(music, loop);
}

void Music::Pause() {
    if (Mix_PausedMusic() == 0) {
        Mix_PauseMusic();
    } else {
        printf("Music is already Paused!\n");
    }
}

void Music::Resume() {
    if (Mix_PausedMusic() == 1) {
        Mix_ResumeMusic();
    } else {
        printf("Music is already playing\n");
    }
}

Music::~Music() {
    Mix_FreeMusic(music);
}