#ifndef SOUNDEFFECTS_H  // Header guard to prevent multiple inclusions
#define SOUNDEFFECTS_H

#include "iostream"    // Include for standard input/output operations
#include "Sound.h"     // Include the base Sound class for inheritance
#include "SDL_Mixer.h" // Include SDL_mixer for audio functionality
using namespace std;   // Use the standard namespace

// SoundEffects class declaration, inheriting from Sound
class SoundEffects : public Sound
{
    public:
        // Constructor to load a sound effect from the specified file path
        SoundEffects(string path);

        // Deleted copy constructor to prevent copying of SoundEffects objects
        SoundEffects(const SoundEffects&) = delete;

        // Deleted assignment operator to prevent assignment of SoundEffects objects
        SoundEffects& operator=(const SoundEffects&) = delete;

        // Deleted default constructor to enforce the use of the parameterized constructor
        SoundEffects() = delete;

        // Method to play the sound effect
        void Play(int loop = 0);

        // Method to pause the sound effect (currently empty)
        void Pause();

        // Method to resume the sound effect (currently empty)
        void Resume();

        // Destructor to clean up resources
        virtual ~SoundEffects();

    private:
        Mix_Chunk* chunk;  // Pointer to the SDL_mixer chunk representing the sound effect
};

#endif // SOUNDEFFECTS_H  // End of header guard
