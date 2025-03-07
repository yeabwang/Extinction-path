#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <Screen.h>


class SplashScreen : public Screen
{
    public:
        /// for description of these functions see Screens.h
        SplashScreen(SDL_Event* e,SDL_Window* gWindow,SDL_Renderer* gRenderer,string Path,int width, int height);
        bool IsEnable();
        void setEnabled(bool e);
        int getButtonPresed();
        void Render();
        Point getSize();
        virtual ~SplashScreen();

    protected:
        bool  Enable;
        Sprites* Background;
        Point Size;
        SDL_Event* e;

    private:
};

#endif // SPLASHSCREEN_H
