#include "SDL.h"          // Include SDL library for core functionality
#include "SDL_image.h"    // Include SDL_image library for image loading and manipulation
#include "SDL_mixer.h"    // Include SDL_mixer library for audio playback and mixing
#include "iostream"       // Include iostream for standard input/output operations
#include "Game.h"        // Include custom Game class header
#include "ctime"         // Include ctime for time-related functions
#include "time.h"        // Include time.h for time-related functions (legacy)
#include "cstdlib"       // Include cstdlib for general utilities like rand()
using namespace std;     // Use the standard namespace

// Function prototype for initializing SDL components
bool Initialize_components();

// Main function: Entry point of the program
int main(int argc, char* argv[])
{
    srand(time(NULL));  // Seed the random number generator with the current time
    Game game(1440, 900, NULL);  // Create an instance of the Game class with a resolution of 1440x900
    return 0;  // Return 0 to indicate successful program termination
}

// Function to initialize SDL and its extensions (SDL_image and SDL_mixer)
bool Initialize_components()
{
    // Initialize SDL with video and audio subsystems
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        return false;  // Return false if SDL initialization fails
    else
    {
        int imgFlags = IMG_INIT_PNG;  // Set flags to initialize PNG image support
        // Initialize SDL_image with PNG support
        if (!(IMG_Init(imgFlags) & imgFlags))
        {
            // Print an error message if SDL_image initialization fails
            cout << "SDL_image could not initialize! SDL_image Error:" << IMG_GetError() << endl;
            return false;  // Return false if SDL_image initialization fails
        }
        // Initialize SDL_mixer for audio playback
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            // Print an error message if SDL_mixer initialization fails
            cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n" << Mix_GetError() << endl;
            return false;  // Return false if SDL_mixer initialization fails
        }
        else
            return true;  // Return true if all components are initialized successfully
    }
}
