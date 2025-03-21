#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>
#include "Sprites.h"
#include "SoundEffects.h"
#include <cstdio> 

class Button
{
public:
    Button(SDL_Renderer* gRenderer, SDL_Window* gWindow, const char* path, Point position, Point size);
    Button(const Button&) = delete; 
    Button& operator=(const Button&) = delete; 
    Button() = delete; 
    bool IsClicked(SDL_Event* e); // Returns true if the button is clicked
    void Render(); // Renders the button
    void UnClick(); // Unclicks the button
    ~Button();

protected:
    bool clicked;
    bool In_Focus = false;
    Point Size;
    Point Position;
    Sprites** listOfSprites;
    SoundEffects* sound[2];
    int cs = 0;

private:
    // None
};

#endif // BUTTON_H