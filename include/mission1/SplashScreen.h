#ifndef SPLASHSCREEN_H  // Header guard to prevent multiple inclusions
#define SPLASHSCREEN_H

#include <Screen.h>  // Include the base Screen class for inheritance

// SplashScreen class declaration, inheriting from Screen
class SplashScreen : public Screen
{
    public:
        // Constructor for the SplashScreen class
        SplashScreen(SDL_Event* e, SDL_Window* gWindow, SDL_Renderer* gRenderer, string Path, int width, int height);

        // Method to check if the SplashScreen is enabled
        bool IsEnable();

        // Method to set the enabled state of the SplashScreen
        void setEnabled(bool e);

        // Method to check if a button (e.g., Enter key) is pressed
        int getButtonPresed();

        // Method to render the SplashScreen
        void Render();

        // Method to get the size of the background sprite
        Point getSize();

        // Destructor for the SplashScreen class
        virtual ~SplashScreen();

    protected:
        bool Enable;          // Flag to indicate if the SplashScreen is enabled
        Sprites* Background;  // Pointer to the background sprite
        Point Size;           // Size of the background sprite
        SDL_Event* e;        // Pointer to SDL_Event for handling input events

    private:
        // No private members or methods in this class
};

#endif // SPLASHSCREEN_H  // End of header guard
