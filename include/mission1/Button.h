#ifndef BUTTON_H
#define BUTTON_H
#include <SDL.h>
#include "Sprites.h"
#include "SoundEffects.h"
class Button
{
    public:
        Button(SDL_Renderer* gRenderer,SDL_Window* gWindow,string path,Point position,Point size);
        Button(const& Button) = delete;///deleted this because we won't make any copy
        Button& operator=(const& Button) = delete;///deleted this because we won't make any assignment
        Button()=delete;///deleted this because we will always use overloaded constructor
        bool IsClicked(SDL_Event*);/// returns true if the button is clicked
        void Render();///renders button
        void UnClick();/// Unclicks the button
        ~Button();

    protected:
        bool clicked;
        bool In_Focus = false;
        Point Size;
        Point Position;
        Sprites** listOfSprites;
        SoundEffects* sound[2];
        int cs =0;
    private:
};

#endif // BUTTON_H


