#ifndef GAME_H
#define GAME_H
#include "SDL.h"
#include "SDL_image.h"
#include "Point.h"
#include "List.h"
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
class LoadandSave; /// To be declared
class GameObjects; /// To be declared
class Screen; /// To be declared
class Missions; /// Forward declaration for Missions

class Game
{
public:
    SDL_Rect screen;
    Game(int, int, LoadandSave*); /// Constructor of game
    void LoadGame(); /// Loads game
    void SaveGame(); /// Saves game
    void GameLogic();
    void ObjectsManager(); /// Adds objects in list and deallocates objects
    bool EventController(); /// Controls events
    virtual ~Game();
    int Current_Stage = 1000;
    bool free = true;

protected:
    SplashScreen* splashScreen;
    Menu* menu;
    PauseScreen* pauseScreen;
    WinScreen* win;
    WinScreen* lose;
    Missions* missions; /// Declare Missions as a member variable
    int counter;
    GameScreen* gs;
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
    bool roundScreenShown = false; /// Flag to track if the round screen has been shown for the current round
    GameObjects* hero;

    friend ofstream& operator<<(ofstream& file, Game* game);
    friend ifstream& operator>>(ifstream& file, Game* game);

private:
};

#endif // GAME_H