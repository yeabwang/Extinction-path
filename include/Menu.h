#ifndef MENU_H
#define MENU_H
#include "Button.h"
#include <Screen.h>

class Menu : public Screen
{
    public:
        /// for description of these functions see Screens.h
        Menu(SDL_Event* e,SDL_Window* gWindow,SDL_Renderer* gRenderer,string Path,int width, int height);
        bool IsEnable();
        void setEnabled(bool e);
        int getButtonPresed();
        void Render();
        Point getSize();
        virtual ~Menu();

    protected:
        bool  Enable;
        Sprites* Background;//SPRITE
        Button* Buttons[3];
        Point Size;
        SDL_Event* e;

    private:
};

#endif // MENU_H
