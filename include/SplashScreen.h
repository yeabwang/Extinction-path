#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include "Screen.h"
#include "Sprites.h"
#include <SDL.h>

class SplashScreen : public Screen {
public:
    SplashScreen(SDL_Event* e, SDL_Window* gWindow, SDL_Renderer* gRenderer, const char* Path, int width, int height); // Changed from std::string to const char*
    bool IsEnable();
    void setEnabled(bool e);
    int getButtonPresed();
    void Render();
    Point getSize();
    virtual ~SplashScreen();

protected:
    bool Enable;
    Sprites* Background;
    Point Size;
    SDL_Event* e;
};

#endif // SPLASHSCREEN_H