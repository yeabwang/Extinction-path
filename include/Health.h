#ifndef HEALTH_H
#define HEALTH_H

#include "Sprites.h"
#include <SDL.h>

class Health
{
public:
    Health(int health, SDL_Window* gWindow, SDL_Renderer* gRenderer, int posx, int posy);
    void display(int x, int y);
    void set_Health(int health);
    void increase(int n);
    void decrease(int n);
    int get_Health();
    virtual ~Health();

protected:
    // None

private:
    int intitalHealth;
    int cs = 1;
    int health;
    SDL_Rect* dRect;
    SDL_Rect* dRect1;
    Sprites* bar[4]{ NULL };
};

#endif // HEALTH_H