#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H



#include "Button.h"
#include <Screen.h>
#include "Sprites.h"


class PauseScreen: public Screen
{
    public:
        PauseScreen(SDL_Event* e,SDL_Window* gWindow,SDL_Renderer* gRenderer,string Path,int width, int height);
        bool IsEnable();
        void setEnabled(bool e);
        int getButtonPresed();
        void Render();
        Point getSize();
        virtual ~PauseScreen();
    protected:
        bool  Enable;
        Sprites* Background;
        Button* Buttons[2];
        Point Size;
        SDL_Event* e;

    private:
};


#endif // PAUSESCREEN_H
