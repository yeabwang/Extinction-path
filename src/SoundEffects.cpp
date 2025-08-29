#include "SoundEffects.h"

SoundEffects::SoundEffects(const char* path) {
    chunk = Mix_LoadWAV(path);
    if (!chunk) {
        printf("Unable to load effect: %s\n", Mix_GetError());
    }
}

void SoundEffects::Play(int loop) {
    Mix_PlayChannel(-1, chunk, loop);
}

void SoundEffects::Pause() {
    // None
}

void SoundEffects::Resume() {
    // None
}

SoundEffects::~SoundEffects() {
    Mix_FreeChunk(chunk);
}