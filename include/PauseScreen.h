#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include "Button.h"
#include "Screen.h"
#include "Sprites.h"
#include <SDL.h>

class PauseScreen : public Screen {
public:
    PauseScreen(SDL_Event* e, SDL_Window* gWindow, SDL_Renderer* gRenderer, const char* Path, int width, int height); // Changed from std::string to const char*
    bool IsEnable();
    void setEnabled(bool e);
    int getButtonPresed();
    void Render();
    Point getSize();
    virtual ~PauseScreen();

protected:
    bool Enable;
    Sprites* Background;
    Button* Buttons[2];
    Point Size;
    SDL_Event* e;
};

#endif // PAUSESCREEN_H