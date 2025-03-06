#ifndef GAMESCREEN_H
#define GAMESCREEN_H
#include "Button.h"
#include "Sprites.h"
#include "Screen.h"
#include "List.h"
#include "GameObjects.h"



class Hero;
class GameScreen:public Screen
{
    public:

        GameScreen(SDL_Event* e,SDL_Window* gWindow,SDL_Renderer* gRenderer,string Path,int width, int height,Hero* hero,List<GameObjects*>* mainList);
        GameScreen()=delete;///deleted this because we will always use overloaded constructor
        GameScreen(const& GameScreen)=delete; ///deleted this because we won't make any copy
        GameScreen& operator=(const GameScreen&) = delete;///deleted this because we won't make any assignment

        /// for the description of these function see Screen.h
        bool IsEnable();
        void setEnabled(bool e);
        int getButtonPresed();
        void Render();
        Point getSize();
        void move(int x);
        bool IsMoved();
        virtual ~GameScreen();

    protected:
        SDL_Renderer* gRenderer;
        SDL_Window * gWindow;
        int coordX =0;
        bool moved = false; ///checks if the background was moved
        Hero* hero;/// stores heroes pointer because backgrounds movement is dependent on hero's movement
        bool  Enable;
        Sprites* Background;
        Button* ButtonsList[1];
        Point Size;
        List<GameObjects*>* mainList;
        SDL_Event* e;

    private:
};

#endif // GAMESCREEN_H
