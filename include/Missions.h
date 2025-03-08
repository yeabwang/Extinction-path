#ifndef MISSIONS_H
#define MISSIONS_H

#include "Button.h"
#include "Screen.h"
#include "Sprites.h"

class Missions : public Screen
{
public:
Missions(SDL_Event* e, SDL_Window* gWindow, SDL_Renderer* gRenderer, string Path, int width, int height);
    bool IsEnable();
    void setEnabled(bool e);
    int getButtonPresed();
    void Render();
    Point getSize();
    void setRoundNumber(int round); // Add this method
    virtual ~Missions();

protected:
    bool Enable;
    Sprites* Background;
    Button* Buttons[2];
    Point Size;
    SDL_Event* e;
    int roundNumber; // Add this member
};

#endif // MISSIONS_H