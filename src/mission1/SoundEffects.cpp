#include "SoundEffects.h"  // Include the SoundEffects class header file

// Constructor for the SoundEffects class
SoundEffects::SoundEffects(string path)
{
    // Load the sound effect from the specified file path
    chunk = Mix_LoadWAV(path.c_str());
    if (!chunk)  // Check if the sound effect failed to load
        cout << "Unable to load effect\n";  // Print an error message
}

// Method to play the sound effect
void SoundEffects::Play(int loop)
{
    // Play the sound effect on any available channel, with the specified number of loops
    Mix_PlayChannel(-1, chunk, loop);
}

// Method to pause the sound effect (currently empty)
void SoundEffects::Pause()
{
    // No implementation yet
}

// Method to resume the sound effect (currently empty)
void SoundEffects::Resume()
{
    // No implementation yet
}

// Destructor for the SoundEffects class
SoundEffects::~SoundEffects()
{
    // Free the memory allocated for the sound effect chunk
    Mix_FreeChunk(chunk);
}
