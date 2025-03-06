#ifndef PAUSESCREEN_H  // Header guard to prevent multiple inclusions
#define PAUSESCREEN_H

#include "Button.h"  // Include the Button class for interactive buttons
#include <Screen.h>  // Include the base Screen class for inheritance
#include "Sprites.h" // Include the Sprites class for rendering the background

// PauseScreen class declaration, inheriting from Screen
class PauseScreen : public Screen
{
    public:
        // Constructor for the PauseScreen class
        PauseScreen(SDL_Event* e, SDL_Window* gWindow, SDL_Renderer* gRenderer, string Path, int width, int height);

        // Method to check if the PauseScreen is enabled
        bool IsEnable();

        // Method to set the enabled state of the PauseScreen
        void setEnabled(bool e);

        // Method to check which button is pressed
        int getButtonPresed();

        // Method to render the PauseScreen
        void Render();

        // Method to get the size of the PauseScreen
        Point getSize();

        // Destructor for the PauseScreen class
        virtual ~PauseScreen();

    protected:
        bool Enable;          // Flag to indicate if the PauseScreen is enabled
        Sprites* Background;  // Pointer to the background sprite
        Button* Buttons[2];   // Array of buttons (Resume and Quit)
        Point Size;           // Size of the PauseScreen
        SDL_Event* e;         // Pointer to SDL_Event for handling input events

    private:
        // No private members in this class
};

#endif // PAUSESCREEN_H  // End of header guard
