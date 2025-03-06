#ifndef MUSIC_H  // Header guard to prevent multiple inclusions
#define MUSIC_H

#include "Sound.h"    // Include the base Sound class for inheritance
#include "SDL_mixer.h" // Include SDL_mixer for music functionality

// Music class declaration, inheriting from Sound
class Music : public Sound
{
    public:
        // Constructor to load music from the specified file path
        Music(string path);

        // Deleted copy constructor to prevent copying of Music objects
        Music(const Music&) = delete;

        // Deleted assignment operator to prevent assignment of Music objects
        Music& operator=(const Music&) = delete;

        // Deleted default constructor to enforce the use of the parameterized constructor
        Music() = delete;

        // Method to play the music
        void Play(int loop = -1);

        // Method to pause the music
        void Pause();

        // Method to resume the music
        void Resume();

        // Destructor to clean up resources
        virtual ~Music();

    protected:
        // No protected members in this class

    private:
        Mix_Music* music;  // Pointer to the SDL_music object representing the music
};

#endif // MUSIC_H  // End of header guard
