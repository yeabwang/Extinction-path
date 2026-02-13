#ifndef WINSCREEN_H
#define WINSCREEN_H

#include "SDL.h"
#include "Point.h"
#include "Sprites.h"

class WinScreen {
public:
    WinScreen(SDL_Event* e, SDL_Window* gWindow, SDL_Renderer* gRenderer, const char* Path, int width, int height); // Changed from std::string to const char*
    bool IsEnable();
    void setEnabled(bool e);
    int getButtonPresed();
    void Render();
    Point getSize();
    virtual ~WinScreen();

protected:
    bool Enable;
    Sprites* Background; // SPRITE
    Point Size;
    SDL_Event* e;
};

#endif // WINSCREEN_H