#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_image.h"
#include "Point.h"
#include "List.h"
#include "Bullet.h"
#include "Hero.h"
#include "Menu.h"
#include "SplashScreen.h"
#include "PauseScreen.h"
#include "Music.h"
#include "WinScreen.h"

// Forward declarations
class LoadandSave;
class GameObjects;
class Screen;
class Missions;

class Game
{
public:
    SDL_Rect screen;
    Game(int width, int height, LoadandSave* file); // Constructor
    void LoadGame(); // Loads game
    void SaveGame(); // Saves game
    void GameLogic();
    void ObjectsManager(); // Manages objects in the list
    bool EventController(); // Handles events
    virtual ~Game(); // Destructor

    int Current_Stage;
    bool free;

protected:
    SplashScreen* splashScreen;
    Menu* menu;
    PauseScreen* pauseScreen;
    WinScreen* win;
    WinScreen* lose;
    Missions* missions;
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
    int EnemyKillCount;
    int OnScreenEnemies;
    bool TankKilled;
    bool TankGenerated;
    bool HelicopterKilled;
    bool HelicopterGenerated;
    bool FinalEnemiesGenerated;
    bool BossGenerated;
    bool roundScreenShown; // Flag to track if the round screen has been shown
    GameObjects* hero;

    friend void SaveGameToFile(FILE* file, Game* game);
    friend void LoadGameFromFile(FILE* file, Game* game);

private:
    bool Initialize_components(); 
};

#endif // GAME_H