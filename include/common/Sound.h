#ifndef SOUND_H  // Header guard to prevent multiple inclusions
#define SOUND_H

#include "SDL.h"        // Include SDL library for core functionality
#include "SDL_mixer.h"  // Include SDL_mixer for audio functionality
#include "iostream"     // Include for standard input/output operations

using namespace std;    // Use the standard namespace

// Sound class declaration (abstract base class)
class Sound
{
    public:
        // Pure virtual method to play the sound
        // Parameters:
        //   - loop: Number of times to loop the sound (-1 for infinite looping)
        virtual void Play(int loop = -1) = 0;

        // Pure virtual method to pause the sound
        virtual void Pause() = 0;

        // Pure virtual method to resume the sound
        virtual void Resume() = 0;

        // Virtual destructor to ensure proper cleanup in derived classes
        virtual ~Sound() {}
};

#endif // SOUND_H  // End of header guard
