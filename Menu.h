#ifndef MENU_H
#define MENU_H

#include "Button.h"
#include "Screen.h"
#include <SDL.h>

class Menu : public Screen {
public:
    Menu(SDL_Event* e, SDL_Window* gWindow, SDL_Renderer* gRenderer, const char* Path, int width, int height); 
    bool IsEnable();
    void setEnabled(bool e);
    int getButtonPresed();
    void Render();
    Point getSize();
    virtual ~Menu();

protected:
    bool Enable;
    Sprites* Background; // SPRITE
    Button* Buttons[3];
    Point Size;
    SDL_Event* e;
};

#endif // MENU_H