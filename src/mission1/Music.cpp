#include "Music.h"  // Include the Music class header file

// Constructor for the Music class
Music::Music(string path)
{
    // Load the music file from the specified path
    music = Mix_LoadMUS(path.c_str());
    if (music == NULL)  // Check if the music failed to load
        cout << "Unable to load Music!\n";  // Print an error message
}

// Method to play the music
void Music::Play(int loop)
{
    // Play the music with the specified number of loops (-1 for infinite looping)
    Mix_PlayMusic(music, loop);
}

// Method to pause the music
void Music::Pause()
{
    if (Mix_PausedMusic() == 0)  // Check if the music is currently playing
        Mix_PauseMusic();  // Pause the music
    else
        cout << "Music is already Paused!\n";  // Print a message if the music is already paused
}

// Method to resume the music
void Music::Resume()
{
    if (Mix_PausedMusic() == 1)  // Check if the music is currently paused
        Mix_ResumeMusic();  // Resume the music
    else
        cout << "Music is already playing\n";  // Print a message if the music is already playing
}

// Destructor for the Music class
Music::~Music()
{
    Mix_FreeMusic(music);  // Free the memory allocated for the music
}
