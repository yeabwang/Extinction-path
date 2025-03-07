#ifndef WINSCREEN_H
#define WINSCREEN_H
#include "SDL.h"
#include "Point.h"
#include "Sprites.h"
#include "iostream"
class WinScreen
{
    public:
        WinScreen(SDL_Event* e,SDL_Window* gWindow,SDL_Renderer* gRenderer,string Path,int width, int height);

        bool IsEnable();


        void setEnabled(bool e);

        int getButtonPresed();
        void Render();
        Point getSize();
        virtual ~WinScreen();

    protected:
        bool  Enable;
        Sprites* Background;//SPRITE
        Point Size;
        SDL_Event* e;

    private:
};

#endif // WINSCREEN_H
#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <Screen.h>



#endif // SPLASHSCREEN_H
