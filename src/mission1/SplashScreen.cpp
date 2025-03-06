#include "SplashScreen.h"  // Include the SplashScreen class header file

// Constructor for the SplashScreen class
SplashScreen::SplashScreen(SDL_Event* e, SDL_Window* gWindow, SDL_Renderer* gRenderer, string Path, int width, int height)
{
    // Initialize the background sprite using the provided path, dimensions, and renderer
    this->Background = new Sprites(gWindow, gRenderer, Path, 1, 0, 0, 1440, 900, width, height, "");
    this->e = e;  // Store the SDL_Event pointer
    Enable = false;  // Initialize the Enable flag to false
}

// Method to check if the SplashScreen is enabled
bool SplashScreen::IsEnable()
{
    return Enable;  // Return the current state of the Enable flag
}

// Method to set the enabled state of the SplashScreen
void SplashScreen::setEnabled(bool e)
{
    Enable = e;  // Update the Enable flag with the provided value
}

// Method to check if a button (e.g., Enter key) is pressed
int SplashScreen::getButtonPresed()
{
    // Check if the event type is a key press and if the key is the Enter key
    if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_RETURN)
    {
        return 1;  // Return 1 if the Enter key is pressed
    }
    return 0;  // Return 0 if no button is pressed
}

// Method to render the SplashScreen
void SplashScreen::Render()
{
    this->Background->render();  // Render the background sprite
}

// Method to get the size of the background sprite
Point SplashScreen::getSize()
{
    return Background->get_Size();  // Return the size of the background sprite
}

// Destructor for the SplashScreen class
SplashScreen::~SplashScreen()
{
    delete Background;  // Clean up the dynamically allocated background sprite
}
