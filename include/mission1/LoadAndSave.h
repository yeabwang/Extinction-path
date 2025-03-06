#ifndef LOADANDSAVE_H
#define LOADANDSAVE_H
#include "List.h"
#include "GameObjects.h"
#include "iostream"
#include "fstream"
#include "Hero.h"
#include "Enemy.h"
#include "Game.h"
#include "Tank.h"
#include "GameScreen.h"
#include "Helicopter.h"
#include  "Boss.h"
#include "Obstacles.h"

class LoadAndSave
{
    public:
        LoadAndSave(Game* game,GameScreen* gamescreen,SDL_Window* window,SDL_Renderer* renderer);
        bool Save(List<GameObjects*>* list, string path);
        bool Load(List<GameObjects*>* list,string path);
        virtual ~LoadAndSave();
    protected:

    private:
        GameScreen* gamescreen;
        SDL_Renderer* gRenderer;
        SDL_Window* gWindow;
        Game* game;
};




#endif // LOADANDSAVE_H
