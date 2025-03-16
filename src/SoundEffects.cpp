#include "SoundEffects.h"

SoundEffects::SoundEffects(const char* path) {
    chunk = Mix_LoadWAV(path);
    if (!chunk) {
        printf("Unable to load effect: %s\n", Mix_GetError());
    }
}

void SoundEffects::Play(int loop) {
    if (isValid()) {
        Mix_PlayChannel(-1, chunk, loop);
    }
}

void SoundEffects::Pause() {
    // SDL_mixer doesn't support pausing individual channels easily
    // If you need this, you'd use Mix_Pause(channel) with a tracked channel ID
}

void SoundEffects::Resume() {
    // SDL_mixer doesn't support resuming individual channels easily
    // If you need this, you'd use Mix_Resume(channel) with a tracked channel ID
}

SoundEffects::~SoundEffects() {
    if (chunk) { // Safe null check
        Mix_FreeChunk(chunk);
        chunk = nullptr; // Prevent double-free (optional, since object is destroyed)
    }
}