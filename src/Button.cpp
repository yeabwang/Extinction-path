#include "Button.h"
#include <cstdlib>
#include <cstring>

Button::Button(SDL_Renderer* gRenderer, SDL_Window* gWindow, const char* path, Point position, Point size)
{
    Size.set_X(size.get_X());
    Size.set_Y(size.get_Y());
    Position.set_X(position.get_X());
    Position.set_Y(position.get_Y());
    this->listOfSprites = new Sprites * [3]{ NULL };
    this->sound[0] = new SoundEffects("data\\Buttons\\Sounds\\Click.wav");
    this->sound[1] = new SoundEffects("data\\Buttons\\Sounds\\focus.wav");
    this->clicked = false;

    // Load all three states of the button
    char num[] = "012";
    char modifiedPath[256];
    for (int i = 0; i < 3; i++)
    {
        strcpy(modifiedPath, path);
        char* dot = strrchr(modifiedPath, '.');
        if (dot)
        {
            *(dot - 1) = num[i];
        }
        this->listOfSprites[i] = new Sprites(gWindow, gRenderer, modifiedPath, 1, position.get_X(), position.get_Y(), size.get_X(), size.get_Y(), size.get_X(), size.get_Y(), "Button", true);
    }
}

bool Button::IsClicked(SDL_Event* e)
{
    clicked = false;
    static bool down = false;

    if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP || e->type == SDL_MOUSEMOTION)
    {
        bool inRange = false;
        int mX = 0;
        int mY = 0;
        SDL_GetMouseState(&mX, &mY);

        if ((Position.get_X() <= mX && Size.get_X() + Position.get_X() >= mX) &&
            ((Position.get_Y() <= mY && Size.get_Y() + Position.get_Y() >= mY)))
        {
            if (!In_Focus)
            {
                In_Focus = true;
                sound[1]->Play();
            }
            inRange = true;
            cs = 2;
        }
        else
        {
            In_Focus = false;
            inRange = false;
            cs = 0;
        }

        if (e->button.button == SDL_BUTTON_LEFT)
        {
            if (e->type == SDL_MOUSEBUTTONDOWN && inRange)
            {
                down = true;
                cs = 1;
            }
            else if (e->type == SDL_MOUSEBUTTONUP && inRange)
            {
                cs = 2;
                down = false;
                if (inRange)
                {
                    clicked = true;
                    sound[0]->Play();
                }
            }
            else if (down && inRange)
            {
                cs = 1;
            }
        }
    }
    return clicked;
}

void Button::Render()
{
    this->listOfSprites[cs]->render();
}

void Button::UnClick()
{
    clicked = false;
}

Button::~Button()
{
    for (int i = 0; i < 3; i++)
    {
        delete listOfSprites[i];
    }
    for (int i = 0; i < 2; i++)
    {
        delete sound[i];
    }
    delete[] listOfSprites;
}