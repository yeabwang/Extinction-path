#ifndef GAME_H
#define GAME_H
#include "SDL.h"
#include "SDL_image.h"
#include "Point.h"
#include  "List.h"
#include "Bullet.h"
#include "Hero.h"
#include "iostream"
#include "Menu.h"
#include "SplashScreen.h"
#include "PauseScreen.h"
#include "Music.h"
#include "WinScreen.h"
using namespace std;
bool Initialize_components();
class LoadandSave;///to be declared
//class Point;///to be declared
class GameObjects;///to be declared
//class List;///to be declared
class Screen;///to be declared
//class Sound;///to be declared



class Game
{
    public:
        SDL_Rect screen;
        Game(int,int,LoadandSave*); /// constructor of game
        void LoadGame(); /// loads game
        void SaveGame(); /// saves game
        void GameLogic();
        void ObjectsManager(); /// adds objects in list and deallocates objects
        bool EventController(); ///controls events
        virtual ~Game();
        int Current_Stage = 1000;
        bool free = true;

    protected:
        SplashScreen* splashScreen;

        Menu* menu;
        PauseScreen* pauseScreen;
        WinScreen* win;
        WinScreen* lose;
        int counter;
        GameScreen*  gs;
        List<GameObjects*> ListofObjects;
        List<Bullet*> EnemyBullets;
        SDL_Window* gWindow;
        SDL_Renderer* gRenederer;
        Point WindowSize;
        SDL_Event e;
        bool Quit;
        Music* themeMusic;
        LoadandSave* File;
        int EnemyKillCount = 0;
        int OnScreenEnemies = 0;
        bool TankKilled = false;
        bool TankGenerated = false;
        bool HelicopterKilled = false;
        bool HelicopterGenerated = false;
        bool FinalEnemiesGenerated = false;
        bool BossGenerated = false;
        GameObjects* hero;


        friend  ofstream& operator<<(ofstream& file,Game* game);
        friend  ifstream& operator>>(ifstream& file,Game* game);
    private:
};

#endif // GAME_H


