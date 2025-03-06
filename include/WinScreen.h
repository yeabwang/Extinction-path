#ifndef WINSCREEN_H  // Header guard to prevent multiple inclusions
#define WINSCREEN_H

#include "SDL.h"      // Include SDL library for core functionality
#include "Point.h"    // Include Point class for size and position representation
#include "Sprites.h"  // Include Sprites class for handling sprite objects
#include "iostream"   // Include iostream for standard input/output operations

// WinScreen class declaration
class WinScreen
{
    public:
        // Constructor for the WinScreen class
        WinScreen(SDL_Event* e, SDL_Window* gWindow, SDL_Renderer* gRenderer, string Path, int width, int height);

        // Method to check if the WinScreen is enabled
        bool IsEnable();

        // Method to set the enabled state of the WinScreen
        void setEnabled(bool e);

        // Method to check if a button (e.g., Enter key) is pressed
        int getButtonPresed();

        // Method to render the WinScreen
        void Render();

        // Method to get the size of the background sprite
        Point getSize();

        // Destructor for the WinScreen class
        virtual ~WinScreen();

    protected:
        bool Enable;          // Flag to indicate if the WinScreen is enabled
        Sprites* Background;  // Pointer to the background sprite
        Point Size;           // Size of the background sprite
        SDL_Event* e;        // Pointer to SDL_Event for handling input events

    private:
        // No private members or methods in this class
};

#endif // WINSCREEN_H  // End of header guard

#ifndef SPLASHSCREEN_H  // Header guard for SplashScreen (unrelated to WinScreen)
#define SPLASHSCREEN_H

#include <Screen.h>  // Include Screen class (unrelated to WinScreen)

#endif // SPLASHSCREEN_H  // End of header guard for SplashScreen
