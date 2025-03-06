#ifndef MENU_H  // Header guard to prevent multiple inclusions
#define MENU_H

#include "Button.h"  // Include the Button class for interactive buttons
#include <Screen.h>  // Include the base Screen class for inheritance

// Menu class declaration, inheriting from Screen
class Menu : public Screen
{
    public:
        // Constructor for the Menu class
        Menu(SDL_Event* e, SDL_Window* gWindow, SDL_Renderer* gRenderer, string Path, int width, int height);

        // Method to check if the Menu is enabled
        bool IsEnable();

        // Method to set the enabled state of the Menu
        void setEnabled(bool e);

        // Method to check which button is pressed
        int getButtonPresed();

        // Method to render the Menu
        void Render();

        // Method to get the size of the Menu
        Point getSize();

        // Destructor for the Menu class
        virtual ~Menu();

    protected:
        bool Enable;          // Flag to indicate if the Menu is enabled
        Sprites* Background;  // Pointer to the background sprite
        Button* Buttons[3];   // Array of buttons (Start, Load, Quit)
        Point Size;           // Size of the Menu
        SDL_Event* e;         // Pointer to SDL_Event for handling input events

    private:
        // No private members in this class
};

#endif // MENU_H  // End of header guard
