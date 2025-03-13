#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <cstdio> 

bool Initialize_components();

int main(int argc, char* argv[])
{
    srand((unsigned int)time(NULL)); // Seed random number generator

    // Initialize SDL components
    if (!Initialize_components())
    {
        printf("Failed to initialize SDL components!\n");
        return -1;
    }

    // Create the game instance
    Game game(1440, 900, NULL);

    // Clean up SDL components before exiting
    Mix_CloseAudio();
    IMG_Quit();
    SDL_Quit();

    return 0;
}

bool Initialize_components()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Initialize SDL_image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    return true;
}